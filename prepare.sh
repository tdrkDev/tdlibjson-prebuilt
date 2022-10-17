#!/bin/bash -e
echo y | sudo apt install gperf
__DIR__="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

if [ ! -d "td" ]; then
	cd $__DIR__
	git clone https://github.com/tdlib/td.git
	cd td
	cd ..
fi

if [ ! -d "openssl" ]; then
	./build-openssl.sh
	mv third-party/openssl/arm64-v8a/include third-party/openssl/
	mv third-party/openssl $__DIR__
	cd $__DIR__
	
fi

# Need to generate some files first, see https://github.com/tdlib/td/issues/1077#issuecomment-640056388
if [ ! -d "$__DIR__/build/td/prepare_cross_compiling" ]; then
	mkdir -p $__DIR__/build/td/prepare_cross_compiling
	cd $__DIR__/build/td/prepare_cross_compiling

	cmake $__DIR__/td || exit 1
	cmake --build . --target prepare_cross_compiling || exit 1
fi
