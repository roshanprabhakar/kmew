#!/usr/bin/env bash
cd "$(dirname "$0")"

pushd ..
docker build env -t kmew-env
popd
