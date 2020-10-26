#!/bin/sh
npm run build

cd build

git init
git add -A
git commit -m 'deploy'

git push -f git@github.com:lorenzo-pomili/country-select.git main:gh-pages
