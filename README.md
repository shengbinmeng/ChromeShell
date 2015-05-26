Android Chrome shell extracted from the chromium project.

## How to extract

### Build Chrome shell in the chromium project

Refer to <https://code.google.com/p/chromium/wiki/AndroidBuildInstructions> and execute the following command successfully.

	ninja -C out/Release content_shell_apk
	
### Prepare src and manifest file

Make a directory chromeshell/ChromeShell where the project will stay in. Then copy chromium/src/chrome/android/shell/java/src/ to chromeshell/ChromeShell/src/, 
and copy chromium/src/out/Release/gen/chrome\_shell\_manifest/AndroidManifest.xml to chromeshell/ChromeShell/AndroidManifest.xml.

### Prepare resource files

Download [apktool](http://ibotpeaches.github.io/Apktool/). Run `apktool d` against chromium/src/out/Release/apks/ChromeShell.apk, 
and copy res/ from the resulting directory to chromeshell/ChromeShell/res/.

### Prepare the libraries

Make directory chromeshell/ChromeShell/libs/, copy the following files from chromium/src/out/Release/lib.java/ to chromeshell/ChromeShell/libs/:

	base_java.jar, chrome_java.jar, content_java.jar, dom_distiller_java.jar, printing_java.jar, service_tab_launcher_java.jar, sync_java.jar, ui_java.jar.

Then copy the following files from chromium/src/third\_party/android\_tools/sdk/extras/android/support/v7/appcompat/ to chromeshell/ChromeShell/libs/:
android-support-v4.jar, android-support-v7-appcompat.jar.

### Create the Android project

In Eclipse with ADT, select File->Import...->Android->Existing Android Code Into Workspace，and choose chromeshell/ChromeShell to
finish the import. Make sure in project.properties, target=android-21(or higher).