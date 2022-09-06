/**
 * @file 抽象工厂模式.cpp
 * @author https://zhuanlan.zhihu.com/p/83535678
 * @brief 具体情形: 鞋厂为了扩大了业务，不仅只生产鞋子，把运动品牌的衣服也一起生产了。
 * 组成:
	1. 抽象工厂类：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
	2. 具体工厂类：继承于抽象工厂，实现创建对应具体产品对象的方式。
	3. 抽象产品类：它是具体产品继承的父类（基类）。
	4. 具体产品类：具体工厂所创建的对象，就是此类。
 * 特点:
	提供一个接口，可以创建多个产品族中的产品对象。如创建耐克工厂，则可以创建耐克鞋子产品、衣服产品、裤子产品等。
 * 缺陷:
	同工厂方法模式一样，新增产品时，都需要增加一个对应的产品的具体工厂类。
 * @date 2022-09-06
 */

#include <iostream>

// 基类 鞋子
class Shoes
{
public:
	virtual void show() = 0;
	virtual ~Shoes() {}
};

// 耐克球鞋
class NikeShoes : public Shoes
{
public:
	void show() override
	{
		std::cout << "耐克球鞋, 广告语是: Just Do it" << std::endl;
	}

	~NikeShoes()
	{
		std::cout << "NikeShoes 已卖出" << std::endl;
	}
};

// 基类 衣服
class Clothes
{
public:
	virtual void show() = 0;
	virtual ~Clothes() {}
};

// 耐克衣服
class NikeClothes : public Clothes
{
public:
	void show() override
	{
		std::cout << "耐克衣服, 广告语是: Just Do it" << std::endl;
	}

	~NikeClothes()
	{
		std::cout << "NikeClothes 已卖出" << std::endl;
	}
};

// 总工厂
class Factory
{
public:
	virtual Shoes *CreateShoes() = 0;
	virtual Clothes *CreateClothes() = 0;
	virtual ~Factory() {}
};

// 耐克生产链
class NikeProducer : public Factory
{
public:
	Shoes *CreateShoes() override
	{
		return new NikeShoes();
	}

	Clothes *CreateClothes() override
	{
		return new NikeClothes();
	}
};

int main()
{
	// ================ 生产耐克流程 ==================== //
	// 鞋厂开设耐克生产线
	Factory *nikeProducer = new NikeProducer();
	// 生产线产出球鞋
	Shoes *nikeShoes = nikeProducer->CreateShoes();
	// 生产线产出衣服
	Clothes *nikeClothes = nikeProducer->CreateClothes();

	// 球鞋上市
	nikeShoes->show();
	//衣服上市
	nikeClothes->show();

	//释放资源
	delete nikeProducer;
	nikeProducer = nullptr;
	delete nikeShoes;
	nikeShoes = nullptr;
	delete nikeClothes;
	nikeClothes = nullptr;

	return 0;
}