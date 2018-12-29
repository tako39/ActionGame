#ifndef ___Class_Task
#define ___Class_Task

//タスククラス。何かのモジュールはすべてこのTaskクラスを継承する。
class Task {
public:
	virtual ~Task() {}
	virtual void Update() = 0;   //更新処理は必ず継承先で実装する
	virtual void Draw() = 0;     //描画処理は必ず継承先で実装する
};

#endif