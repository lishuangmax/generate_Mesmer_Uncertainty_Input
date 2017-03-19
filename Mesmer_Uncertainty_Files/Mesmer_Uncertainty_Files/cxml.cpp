#include "cxml.h"

CXml::CXml()
{
	doc=new TiXmlDocument();

	strtemp=NULL;
	currelem=NULL;
	rootelem=NULL; 

	return;
}

CXml::~CXml(){//防止内存泄露
	if(strtemp!=NULL)
		delete(strtemp);
}

bool CXml::open(const char *filename)
{
	bool ok=false;
	if(doc->LoadFile(filename)){//成功打开文件
		rootelem=doc->RootElement();
		if(rootelem)//成功获得首个元素
			ok=true;
	}
	return ok;
}


char* CXml::readElementAttr(const char * element,const char * attribute,const char *parent)
{
	char *result=NULL;

	if(element==NULL||attribute==NULL)
		return result;

	//如果有指定父节点得先找到父节点，然后从父节点开始找子节点
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//找不到父节点
			return result;
	}
	if(findElement(rootelem,element,currelem)){
		int len=strlen(currelem->Attribute(attribute));//获取文本的长度
		if(len){//存在text值   
			result=new char[len+1];//申请内存
			strcpy(result,currelem->Attribute(attribute));//拷贝字符串的值
			strtemp=result;//返回值strtext指向同一内存,防止内存泄露 
		}  
	} 
	rootelem=doc->RootElement();//恢复顶级节点的指向为文本的顶节点
	return result;
}

bool CXml::setElementAttr(const char * element,const char* attribute,const char* value,const char *parent)
{
	bool ok=false;
	if(element==NULL||attribute==NULL||value==NULL)
		return ok;
	//如果有指定父节点得先找到父节点，然后从父节点开始找子节点
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//找不到父节点
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		currelem->SetAttribute(attribute,value);
		ok=true;
	}  
	rootelem=doc->RootElement();//恢复顶级节点的指向为文本的顶节点
	doc->SaveFile();//保存操作

	return ok;
}


bool CXml::readElementText(const char *element, char * &text,const char *parent)
{
	bool ok=false;
	unsigned int len=0;

	if(element==NULL)
		return ok;

	if(text!=NULL){
		delete(text);
		text=NULL;
	}
	//如果有指定父节点得先找到父节点，然后从父节点开始找子节点
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//找不到父节点
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		len=strlen(currelem->GetText());//获取文本的长度
		if(len){//存在text值   
			text=new char[len+1];//申请内存
			strcpy(text,currelem->GetText());//拷贝字符串的值
			strtemp=text;//返回值strtext指向同一内存,防止内存泄露 
			ok=true;
		}  
	}
	rootelem=doc->RootElement();//恢复顶级节点的指向为文本的顶节点
	return ok;
}

bool CXml::setElementText(const char * element,const char* value,const char *parent)
{
	bool ok=false;
	if(element==NULL||parent==NULL||value==NULL)
		return ok;
	//如果有指定父节点得先找到父节点，然后从父节点开始找子节点
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//找不到父节点
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		currelem->ReplaceChild(currelem->FirstChild(),TiXmlText(value));
		ok=true;
	}  
	rootelem=doc->RootElement();//恢复顶级节点的指向为文本的顶节点
	doc->SaveFile();//保存操作

	return ok;
}


bool CXml::findElement(TiXmlElement* rootelem,const char *element,TiXmlElement* &node)
{
	bool ok=false;
	if(strcmp(element,rootelem->Value())==0){//比较当前元素的名称和要查找的名称
		node=rootelem;
		ok=true;
	}else{//没找到,先找子节点,再找兄弟节点
		for(TiXmlElement *pelem=rootelem->FirstChildElement();pelem;pelem=pelem->NextSiblingElement()){
			if(findElement(pelem,element,node)){
				ok=true;
				break;
			}
		}
	}
	return ok;
}

bool CXml::findElement(TiXmlElement* rootelem,const char *element,const char *attriname,const char *attrivalue,TiXmlElement* &node)
{
	bool ok=false;
	for(TiXmlElement *pelem=rootelem->FirstChildElement();pelem;pelem=pelem->NextSiblingElement()){
		if(findElement(pelem,element,node)){
			if (strcmp(attrivalue,node->Attribute(attriname))==0)
			{
				ok=true;
				break;
			}			
				
		}
	}
	
	
	return ok;
}