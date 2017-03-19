#include "tinyxml.h"


class  CXml {
public:

	// TODO: add your methods here.

	//读取读取指定元素element的text值,找到该元素,返回true，并且*text指向该值
	//没有该元素，返回false,text指针为NULL
	//parent为element元素的父节点
	bool readElementText(const char * element,char * &text,const char *parent=NULL);

	//设定指定节点element的text值为value,parent为父节点名称
	//设定成功返回true
	bool setElementText(const char * element,const char* value,const char *parent=NULL);

	//读取指定元素element的指定的属性的属性值，找到时返回该属性值
	//没有该元素或者指定属性，返回NULL
	//parent为element元素的父节点
	char* readElementAttr(const char * element,const char * attribute,const char *parent=NULL);

	//设定指定节点element的attribute值为value,parent为父节点名称
	//设定成功返回true
	bool setElementAttr(const char * element,const char* attribute,const char* value,const char *parent=NULL);

	bool open(const char* filename);

	CXml(void);
	~CXml(void);


	TiXmlDocument *doc;//XML文件

	TiXmlElement *currelem;//XML节点元素,当前节点元素
	TiXmlElement *rootelem;//XML节点元素,根节点

	char* strtemp;

public:
	//从文件顶部元素rootelem开始查找名为element的元素
	//找到指定的元素,找到时返回true,f同时返回TiXmlElement类型的要查找的元素node
	bool findElement(TiXmlElement* rootelem,const char *element,TiXmlElement* &node);
	bool findElement(TiXmlElement* rootelem,const char *element,const char *attriname,const char *attrivalue,TiXmlElement* &node);


};