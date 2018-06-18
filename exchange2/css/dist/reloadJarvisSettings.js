var JarvisSettings = JarvisSettings || {};
if (JarvisSettings || {})

for (var jsettings in JarvisSettings || {}) {
  localStorage[jsettings] = JarvisSettings[jsettings];
}

if (JarvisSettings.published) {
  var sheet = window.document.styleSheets[0];
  sheet.insertRule('#ribbon, .demo { display: none!important; }', sheet.cssRules.length);
  sheet.insertRule('[id*="ap-"] header {display: none;}', sheet.cssRules.length);
  sheet.insertRule('[id*="ap-"] [ap-widget] {padding: 0; border: none; background-color: transparent!important;}', sheet.cssRules.length);
}
