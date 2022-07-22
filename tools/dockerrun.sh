#!/usr/bin/env bash
cd "$(dirname "$0")"

pushd ..
docker run --rm -it -v "$(pwd)":/root/env kmew-env
popd
