Android Chrome shell extracted from the chromium project.

## How to extract

Before the extraction, you need to get the chromium code and have a successful build of Android Chrome Shell.
Refer to <https://code.google.com/p/chromium/wiki/AndroidBuildInstructions> and make sure the following command runs successfully.

	ninja -C out/Release chrome_shell_apk
	
### Copy src, res, and manifest file

Make a directory chromeshell/ChromeShell where the project will stay in. Then copy chromium/src/chrome/android/shell/java/src/ to be chromeshell/ChromeShell/src/, 
copy chromium/src/chrome/android/shell/res/ to be chromeshell/ChromeShell/res/, 
and copy chromium/src/out/Release/gen/chrome\_shell\_manifest/AndroidManifest.xml to be chromeshell/ChromeShell/AndroidManifest.xml.

### Create the Android project

In Eclipse with ADT, select File->Import...->Android->Existing Android Code Into Workspace，and choose chromeshell/ChromeShell to
finish the import. Make sure in project.properties, target=android-21(or higher).

### Prepare the native libraries

Unzip the APK you successfully built from the ninja command, and copy out the native libs (libchromeshell.so and libchromium_android_linker.so).
Prepare them as prebuilt libraries in the jni folder.

Besides, copy chromium/src/out/Release/chrome\_shell\_apk/native\_libraries\_java/NativeLibraries.java to be chromeshell/ChromeShell/src/org/chromium/base/library\_loader/NativeLibraries.java.

### Prepare the asset folder

Unzip the APK you successfully built from the ninja command, and copy out the "assets" folder. Put that copy under chromeshell/ChromeShell/.

### Prepare library projects

Make library projects according to chromium/src/out/Release/res.java/: for every library that has resources, we should make a library project using its resources here and its jar file in chromium/src/out/Release/lib.java/.
The src directory of the library project is empty (or doesn't exist at all) since all the codes are in the jar.

The ChromeShell application project depends on these library projects.

### Add other libraries

Make directory chromeshell/ChromeShell/libs/, copy the jar files that are not prepared in above step from chromium/src/out/Release/lib.java/ to chromeshell/ChromeShell/libs/.

Also copy chromium/src/third\_party/android\_tools/sdk/extras/google/gcm/gcm-client/dist/gcm.jar to chromeshell/ChromeShell/libs/.

### Add needed play services modules

The project needs modules from Google's play services library. However, the play services library is so huge that if we import it totally, multidex must be used (See <http://developer.android.com/tools/building/multidex.html>).
With Eclipse, multidex is hard to support, so avoid importing the whole play services library and only add the needed module(s): play-services-cast
(See <https://androiddevx.wordpress.com/2014/10/28/google-play-services-on-a-much-needed-diet/>).