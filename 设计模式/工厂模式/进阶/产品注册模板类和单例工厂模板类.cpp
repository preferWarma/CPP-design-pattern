/**
 * @file 产品注册模板类和单例工厂模板类.cpp
 * @author https://zhuanlan.zhihu.com/p/83537599
 * @brief
	1.板工厂虽然在新增产品的时候，不需要新增具体的工厂类，但是缺少一个可以统一随时随地获取指定的产品对象的类,还有
	改进的空间，我们可以把产品注册的对象用std::map的方式保存，通过key-valve的方式可以轻松简单的获取对应的产品对象实例。
 * 大致思路:
	1.把产品注册的功能封装成产品注册模板类。注册的产品对象保存在工厂模板类的std::map，便于产品对象的获取。
	2.把获取产品对象的功能封装成工厂模板类。为了能随时随地获取指定产品对象，则把工厂设计成单例模式。
 * @date 2022-09-06
 */

#include <iostream>
#include <string>
#include <unordered_map>

// 基类 鞋子
class Shoes
{
public:
	virtual void show() = 0;
	virtual ~Shoes() {}
};

// 耐克鞋子
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

// 优衣库衣服
class UniqloClothes : public Clothes
{
public:
	void show() override
	{
		std::cout << "优衣库衣服, 广告语是: I am Uniqlo" << std::endl;
	}
	~UniqloClothes()
	{
		std::cout << "UniqloClothes 已卖出" << std::endl;
	}
};

// 基类，产品注册模板接口类
// 模板参数 ProductType_t 表示的类是产品抽象类, 如Shoes或Clothes
template <class ProductType_t>
class IProductRegistrar
{
public:
	// 获取产品对象抽象接口(如Shoes或Clothes)
	virtual ProductType_t *CreateProduct() = 0;

protected:
	// 禁止外部构造和析构, 子类的"内部"其他函数可以调用
	IProductRegistrar() {}
	virtual ~IProductRegistrar() {}

private:
	// 禁止外部拷贝构造和赋值操作
	IProductRegistrar(const IProductRegistrar &) {}
	const IProductRegistrar &operator=(const IProductRegistrar &) {}
};

// 工厂模板类，用于获取和注册产品对象
// 模板参数 ProductType_t 表示的类是产品抽象类, 如Shoes或Clothes
template <class ProductType_t>
class ProductFactory
{
public:
	// 单例模式, 保证唯一的工厂实例, 这里采用懒汉式单例模式
	static ProductFactory<ProductType_t> &Instance()
	{
		static ProductFactory<ProductType_t> instance;
		return instance;
	}

	// 产品注册
	void RegisterProduct(IProductRegistrar<ProductType_t> *registrar, const std::string &name)
	{
		m_ProductRegistry[name] = registrar;
	}

	// 根据名字(如"Nike"), 获取对应具体的产品(如NikeShoes)
	ProductType_t *GetProduct(std::string name)
	{
		// 从map找到已经注册过的产品，并返回产品对象
		if (m_ProductRegistry.count(name) != 0)
		{
			return m_ProductRegistry[name]->CreateProduct();
		}
		// 未注册的产品则报错未找到
		std::cout << "No product found for" << name << std::endl;
		return nullptr;
	}

private:
	// 禁止外部构造和析构
	ProductFactory() = default;
	virtual ~ProductFactory() = default;

	// 禁止外部拷贝构造和赋值操作
	ProductFactory(const ProductFactory<ProductType_t> &) {}
	const ProductFactory<ProductType_t> &operator=(const ProductFactory<ProductType_t> &) {}

	// 保存注册过的产品, key: 产品名字(如"Nike"), value: 产品类型(如Shoes)
	std::unordered_map<std::string, IProductRegistrar<ProductType_t> *> m_ProductRegistry;
};

// 产品注册模板类，用于创建具体产品和从工厂里注册产品
// 模板参数 ProductType_t 表示的类是产品抽象类（基类），ProductImpl_t 表示的类是具体产品（产品种类的子类）
template <class ProductType_t, class ConcreteProduct_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t>
{
public:
	// 构造函数， 用于注册产品到工厂, 只能显式调用
	explicit ProductRegistrar(std::string name)
	{
		// 通过工厂单例把产品注册到工厂,
		// 此处仍然使用到了多态, 利用IProductregistrar<ProductType_t>*类型的指针指向子类ProductRegistrar<ProductType_t, ConcreteProduct_t>*指向的对象
		// 使得在IProductregistrar<ProductType_t>单例的注册表成员m_ProductRegistry可以调用具体产品(ConcreteType_t)的构造函数CreteProduct()
		ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
	}

	// 创建具体产品对象指针
	ProductType_t *CreateProduct() override
	{
		return new ConcreteProduct_t();
	}
};

int main()
{
	// ========================== 生产耐克球鞋过程 ===========================//
	// 注册产品种类为Shoes, 产品为NikeShoes到工厂, 产品名为Nike
	ProductRegistrar<Shoes, NikeShoes> nikeShoes("Nike");
	// 从工厂获取产品种类为Shoes, 产品名为Nike的产品对象
	Shoes *pNikeShoes = ProductFactory<Shoes>::Instance().GetProduct("Nike");
	// 生产耐克球鞋
	pNikeShoes->show();
	// 释放资源
	delete pNikeShoes;
	pNikeShoes = nullptr;

	// ========================== 生产优衣库衣服过程 ===========================//
	// 注册产品种类为Clothes, 产品为UniqloClothes到工厂, 产品名为Uniqlo
	ProductRegistrar<Clothes, UniqloClothes> uniqloClothes("Uniqlo");
	// 从工厂获取产品种类为Clothes, 产品名为Uniqlo的产品对象
	Clothes *pUniqloClothes = ProductFactory<Clothes>::Instance().GetProduct("Uniqlo");
	// 生产优衣库衣服
	pUniqloClothes->show();
	// 释放资源
	delete pUniqloClothes;
	pUniqloClothes = nullptr;

	return 0;
}