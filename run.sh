#!/bin/bash

set -euxo pipefail

VERSION=${VERSION:-1}

docker build -t ethan42/snote:$VERSION .
docker push ethan42/snote:$VERSION
mayhem run . --image ethan42/snote:$VERSION
