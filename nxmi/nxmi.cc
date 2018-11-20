#include <node.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <sstream>

#include <node.h>
#include <v8.h>

using namespace v8;
using namespace std;

namespace nxmi {

  using v8::Local;
  using v8::Object;
  void Methodone(const FunctionCallbackInfo<Value>& args) {
    // printf(& args);
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "method one hello"));
  }

  void Methodtwo(const FunctionCallbackInfo<Value>& args) {
      // printf(& args);
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope(isolate);
      args.GetReturnValue().Set(String::NewFromUtf8(isolate, "method one"));
  }

  void Invoke2(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);
        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
        }

        double value = args[0]->NumberValue() + args[1]->NumberValue();
        Local<Number> num = Number::New(isolate, value);

        args.GetReturnValue().Set(num);

  }

  void Invoke1(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    v8::String::Utf8Value yljgdm(args[0]->ToString());
    v8::String::Utf8Value ip(args[1]->ToString());
    v8::String::Utf8Value biztype(args[2]->ToString());
    v8::String::Utf8Value data(args[3]->ToString());
    std::string returnValue = std::string(*yljgdm) + "," + std::string(*biztype) + "," +std::string(*ip) ;
    ::HINSTANCE hDLL = NULL;
    typedef char*(*pHDSerialNumRead)(string,string,string,string);
    hDLL = LoadLibrary("nxmi.dll");

    if(hDLL){
        printf("dll Exists\n");
        pHDSerialNumRead ph=(pHDSerialNumRead)GetProcAddress(hDLL,"node_invoke");
        if (ph){
            printf("333 \n");
            char* p = ph(returnValue,returnValue,returnValue,returnValue);
            DWORD err = GetLastError();
            printf("%u", err);
            char p1[30];
            strcpy(p1,p) ;
        }else{
            DWORD err = GetLastError();
            //std::string returnValue = std::string(err);
           printf("%u", err);
           printf("xxxx");
            /*isolate->ThrowException(Exception::TypeError(
                               String::NewFromUtf8(isolate, "method invoke not Exists")));*/
        };
    }else{
        DWORD err = GetLastError();
        //std::string returnValue = std::string(err);
        printf("%u", err);
        printf("\nxxxx\n");
        isolate->ThrowException(Exception::TypeError(
                  String::NewFromUtf8(isolate, "nxmi.DLL not Exists")));
      /*printf("method \n");
      char* p = ph() ;
      char p1[30];
      strcpy(p1,p) ;
      std::string sno = p1 ;*/
    };
    FreeLibrary(hDLL) ;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, returnValue.c_str()));
  }

  void Invoke(const FunctionCallbackInfo<Value>& args){
     //printf("start call Invoke\n");
      Isolate* isolate = Isolate::GetCurrent();
      HandleScope scope(isolate);
      v8::String::Utf8Value data(args[0]->ToString());

      std::string returnValue = std::string(*data);
      // printf("%s\n",returnValue.c_str());
      ::HINSTANCE hDLL = NULL;
      // printf("start call dll \n");

      typedef void ( __stdcall *node_invoke)(char*,char**);

      char* pBuf = new char[2048];
      memset(pBuf, 0, 2048);
      // char[] indataaaa =returnValue ;
      char* indata  = (char*) returnValue.c_str() ;

      // procedure node_invoke(params : PChar;var result : PChar) ; stdcall ;
      // typedef char*(*pHDSerialNumRead)(string,string,string,string);
      hDLL = LoadLibrary("nxmi.dll");

      if(hDLL){
          // printf("dll Exists\n");
          node_invoke finvoke=(node_invoke)GetProcAddress(hDLL,"node_invoke");
          if (finvoke){
              // printf("%s", indata);
              // printf("111111111111111111111111 \n");
              try{
                char* _result= (char*)malloc(2408);
                 finvoke(indata,&_result);
                 returnValue = _result ;
                 free(_result);
              }catch(exception e){
                DWORD err = GetLastError();
                printf("%u", err);
                isolate->ThrowException(Exception::TypeError(
                                                 String::NewFromUtf8(isolate, "method invoke not Exists")));
              }
          }else{
              DWORD err = GetLastError();
              //std::string returnValue = std::string(err);
              // printf("%u", err);
              // printf("xxxx");
              isolate->ThrowException(Exception::TypeError(
                                 String::NewFromUtf8(isolate, "method invoke not Exists")));
          };
      }else{
          DWORD err = GetLastError();
          //std::string returnValue = std::string(err);
          printf("%u", err);
          // printf("xxxx");
          isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "nxmi.DLL not Exists")));
      };
      FreeLibrary(hDLL) ;
      args.GetReturnValue().Set(String::NewFromUtf8(isolate, returnValue.c_str()));
    }



  void init(Handle<Object> exports) {
    // printf("Hello node & V8 \n");
    NODE_SET_METHOD(exports, "hello", Methodone);
    NODE_SET_METHOD(exports, "invoke", Invoke);
  }


  void hello() {
    printf("Hello node & V8 \n");
  }

  NODE_MODULE(nxmi, init)
}
