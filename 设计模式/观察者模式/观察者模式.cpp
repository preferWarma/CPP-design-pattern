/**
 * @file 观察者模式.cpp
 * @author https://zhuanlan.zhihu.com/p/119308881
 * @brief 核心思想: 一对多。此源代码使用智能指针进行优化
 * @date 2022-09-07
 */
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

// 抽象观察者接口
class ObserverInterface
{
public:
	ObserverInterface() = default;
	virtual ~ObserverInterface() = default;
	virtual void DoSomething() = 0;
};

// 对抽象观察者的智能指针起别名
using pObserverInterface = std::shared_ptr<ObserverInterface>;

// 被观察者接口
class SubjectInterface
{
public:
	// 为当前被观察者添加观察者
	virtual void add(pObserverInterface obj) = 0;
	// 删除当前被观察者的指定观察者
	virtual void erase(pObserverInterface obj) = 0;
	// 对观察者进行广播
	virtual void notify() = 0;
	// 析构函数
	virtual ~SubjectInterface() = default;
};

// 具体的被观察者
class Me : public SubjectInterface
{
public:
	// 将该观察者添加被观察者的观察者链表中(订阅)
	void add(pObserverInterface obj) override
	{
		observers.emplace_back(obj);
	}

	// 将该观察者从被观察者的观察者链表中删除(取消订阅)
	void erase(pObserverInterface obj) override
	{
		// 查找该观察者在观察者链表中的位置
		auto pos = std::find(observers.begin(), observers.end(), obj);
		// 如果存在就删除
		if (pos != observers.end())
		{
			observers.erase(pos);
		}
	}

	// 对整个观察者列表进行广播
	void notify() override
	{
		for (const auto observer : observers)
		{
			observer->DoSomething();
		}
	}

	// 析构函数
	~Me() override
	{
		std::cout << "爸爸工作去了" << std::endl;
	}

private:
	// 记录当前被观察者的所有观察者
	std::list<pObserverInterface> observers;
};

// 具体的观察者
class Son : public ObserverInterface
{
public:
	void DoSomething() override
	{
		std::cout << "爸爸回家了, 不能打游戏了" << std::endl;
	}

	~Son() override
	{
		std::cout << "儿子上学去了" << std::endl;
	}
};

// 具体的观察者
class Mother : public ObserverInterface
{
public:
	void DoSomething() override
	{
		std::cout << "老公回家了, 准备做饭了" << std::endl;
	}

	~Mother() override
	{
		std::cout << "妈妈上班去了" << std::endl;
	}
};

int main()
{
	std::shared_ptr<Me> me = std::make_shared<Me>();
	std::shared_ptr<Mother> wife = std::make_shared<Mother>();
	std::shared_ptr<Son> son = std::make_shared<Son>();

	// 添加订阅
	me->add(wife);
	me->add(son);

	// 给订阅者发消息
	me->notify();

	return 0;
}