// SPDX-License-Identifier: Apache-2.0
// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app/kdbg

#include <ThirdParty/XML/XML.h>

namespace KDbg {

inline bool INavHintsDelegate::Load(const std::string& path) noexcept {
  m_pragmas.clear();
  m_images.clear();
  m_valid = false;

  xmlDoc* doc = xmlReadFile(path.c_str(), nullptr, XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
  if (!doc) return false;

  xmlNode* root = xmlDocGetRootElement(doc);
  if (!root || xmlStrcmp(root->name, BAD_CAST "NavigationHints") != 0) {
    xmlFreeDoc(doc);
    return false;
  }

  for (xmlNode* node = root->children; node; node = node->next) {
    if (node->type != XML_ELEMENT_NODE) continue;

    if (xmlStrcmp(node->name, BAD_CAST "Pragma") == 0) {
      xmlChar* key = xmlGetProp(node, BAD_CAST "Key");
      xmlChar* val = xmlNodeGetContent(node);

      if (key && val) {
        NavHintsPragma pragma;
        pragma.key   = reinterpret_cast<const char*>(key);
        pragma.value = reinterpret_cast<const char*>(val);

        auto trim = [](std::string& s) {
          s.erase(0, s.find_first_not_of(" \t\r\n"));
          auto last = s.find_last_not_of(" \t\r\n");
          if (last != std::string::npos) s.erase(last + 1);
        };
        trim(pragma.value);

        m_pragmas.push_back(std::move(pragma));
      }

      if (key) xmlFree(key);
      if (val) xmlFree(val);

    } else if (xmlStrcmp(node->name, BAD_CAST "Image") == 0) {
      xmlChar* url = xmlGetProp(node, BAD_CAST "url");

      if (url) {
        NavHintsImage img;
        img.url = reinterpret_cast<const char*>(url);
        m_images.push_back(std::move(img));
        xmlFree(url);
      }
    }
  }

  xmlFreeDoc(doc);
  m_valid = true;
  return true;
}

inline std::string INavHintsDelegate::Pragma(const std::string& key) const noexcept {
  for (const auto& p : m_pragmas) {
    if (p.key == key) return p.value;
  }
  return {};
}

const std::vector<NavHintsPragma>& INavHintsDelegate::Pragmas() const noexcept {
  return m_pragmas;
}
const std::vector<NavHintsImage>& INavHintsDelegate::Images() const noexcept {
  return m_images;
}

bool INavHintsDelegate::IsValid() const noexcept {
  return m_valid;
}

}  // namespace KDbg
