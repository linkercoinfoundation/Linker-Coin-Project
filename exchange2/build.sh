#!/bin/bash
rm -rf build && mkdir build
cp *.* build/
rm build/package*.json
cp -r img build/
cp -r js build/
cp -r lang build/
cp -r libs build/
cp -r scss build/
cp -r assets build/
cp -R node_modules/apex-library/build/. build/js/
echo "// `npm info apex-library version`" | cat - node_modules/apex-library/build/library.min.js > build/js/library.min.js
cp -R node_modules/apex-widgets/build/. build/js/
echo "// `npm info apex-widgets version`" | cat - node_modules/apex-widgets/build/widgets.min.js > build/js/widgets.min.js
if [ "$1" == "prod" ]; then
  cp build/js/config-prod.js build/js/config.js
fi
if [ "$1" == "stage" ]; then
  cp build/js/config-stage.js build/js/config.js
fi
