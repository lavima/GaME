/*
* File: V8.cpp
* Author: Lars Vidar Magnusson
*/

#include "../GaME.h"


/*
void GaME::V8::ReportException(v8::TryCatch &tryCatch) {

    v8::HandleScope handleScope;

    v8::String::Utf8Value exception(tryCatch.Exception());
    const char* exceptionString = ToCString(exception);

    v8::Handle<v8::Message> message = tryCatch.Message();

    if (!message.IsEmpty()) {

        String::Utf8Value filename(message->GetScriptResourceName());
        const char* filenameString = ToCString(filename);

        int linenum = message->GetLineNumber();
        printf("%s:%i: %s\n", filenameString, linenum, exceptionString);

        v8::String::Utf8Value stackTrace(tryCatch.StackTrace());
        if (stackTrace.length() > 0) {
            const char* stackTraceString = ToCString(stackTrace);
            printf("%s\n", stackTraceString);
        }
    }
    else
        printf("%s\n", exceptionString);
}

const char *V8::ToCString(const v8::String::Utf8Value &value) {
    return *value ? *value : "Failed to convert to string";
}
*/
