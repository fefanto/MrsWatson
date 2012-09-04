#include "ApplicationRunner.h"

static char* _getTestInputFilename(const char* fileExtension) {
  CharString filename = newCharString();
  snprintf(filename->data, filename->capacity, "resources%caudio%ca440-stereo.%s",
    PATH_DELIMITER, PATH_DELIMITER, fileExtension);
  return filename->data;
}

static LinkedList _argsForScanPlugins(void) {
  LinkedList args = newLinkedList();
  appendItemToList(args, "--list-plugins");
  return args;
}

static LinkedList _argsForProcessWithAgainPlugin(void) {
  LinkedList args = newLinkedList();
  appendItemToList(args, "--plugin");
  appendItemToList(args, "again");
  appendItemToList(args, "--input");
  appendItemToList(args, _getTestInputFilename("pcm"));
  return args;
}

void runMrsWatsonTests(char *applicationPath);
void runMrsWatsonTests(char *applicationPath) {
  runApplicationTest(applicationPath,
    "Run with no plugins", newLinkedList(),
    RETURN_CODE_MISSING_REQUIRED_OPTION, false);
  runApplicationTest(applicationPath,
    "List plugins", _argsForScanPlugins(),
    RETURN_CODE_NOT_RUN, false);
  runApplicationTest(applicationPath,
    "Process with again plugin", _argsForProcessWithAgainPlugin(),
    RETURN_CODE_SUCCESS, true);
}
