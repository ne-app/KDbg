#! /bin/sh

## To be used for curl -fsSL https://install.nekernel.org | sh

echo "==> NE.APP: WELCOME TO THE TIER-ZERO INSTALLER."
echo "==> NE.APP: INSTALLING DISTRIBUTION..."

echo "==> COMING SOON: THE NESYSTEM WILL SOON BE AVAILABLE AS AN API-FIRST EXPERIENCE."

ARCH=x64
PROFILE=release-pc

SRC=tier-zero
VCS=git
FLAGS=clone --recurse-submodules -j8
DIST=tz-${ARCH}-${PROFILE}

mkdir ${DIST}

${GIT} ${FLAGS} https://github.com/ne-app-ci/${SRC}.git ${DIST}/${SRC}
