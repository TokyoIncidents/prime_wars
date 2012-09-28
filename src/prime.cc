#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <vector>
#include <numeric>
#include <math.h>

using namespace std;
using namespace v8;

Handle<Value> Sum(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  int num = args[0]->NumberValue();
  // http://d.hatena.ne.jp/scior/20100922/1285165194
  vector<int> Prime; // 素数リスト
  bool Find[num]; // 探索リスト
  for(int i = 2; i <= num; i++) Find[i] = false;
  for(int i = 2; i < sqrt(num); i++){
      if(Find[i]) continue; // すでに除いた数は飛ばす

      // j++からj+=iになったのでループ内でiの倍数のみが処理される。だいぶ高速化
      for(int j = i * 2; j < num; j += i) {
          if(!Find[j]) Find[j] = true;
      }
  }
  // 2の倍数の素数は2だけなので奇数のみを判定
  Prime.push_back(2);
  for(int i = 3; i < num; i += 2){
      if(!Find[i]) Prime.push_back(i);
  }
  Local<Value> sum = Number::New(accumulate(Prime.begin(), Prime.end(), 0));
  return scope.Close(sum);
}

void Init(Handle<Object> target) {
  target->Set(String::NewSymbol("sum"),
      FunctionTemplate::New(Sum)->GetFunction());
}

NODE_MODULE(prime, Init)
