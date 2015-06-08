Android Chrome shell extracted from the chromium project.

## How to extract

### Build Chrome shell in the chromium project

Refer to <https://code.google.com/p/chromium/wiki/AndroidBuildInstructions> and execute the following command successfully.

	ninja -C out/Release content_shell_apk
	
### Prepare src and manifest file

Make a directory chromeshell/ChromeShell where the project will stay in. Then copy chromium/src/chrome/android/shell/java/src/ to chromeshell/ChromeShell/src/, 
and copy chromium/src/out/Release/gen/chrome\_shell\_manifest/AndroidManifest.xml to chromeshell/ChromeShell/AndroidManifest.xml.

### Create the Android project

In Eclipse with ADT, select File->Import...->Android->Existing Android Code Into Workspace，and choose chromeshell/ChromeShell to
finish the import. Make sure in project.properties, target=android-21(or higher).

### Prepare library projects

Make library projects according to chromium/src/out/Release/res.java/: for every library that has resources, we should make a library project using its resources here and its jar file in chromium/src/out/Release/lib.java/.
The src directory of the library project can be empty since all the codes are in the jar.

The ChromeShell application project depends on these library projects.

### Add other libraries

Make directory chromeshell/ChromeShell/libs/, copy the jar files that are not prepared in above step from chromium/src/out/Release/lib.java/ to chromeshell/ChromeShell/libs/.

Besides, also copy chromium/src/third_party/android_tools/sdk/extras/google/gcm/gcm-client/dist/gcm.jar.

### Add needed play services modules

The project needs modules from Google's play services library. However, the play services library is so huge that if we import it totally, multidex must be used (See <http://developer.android.com/tools/building/multidex.html>).
With Eclipse, multidex is hard to support, so I avoid importing the whole play services library and only add the needed module(s): play-services-cast
(See <https://androiddevx.wordpress.com/2014/10/28/google-play-services-on-a-much-needed-diet/>).