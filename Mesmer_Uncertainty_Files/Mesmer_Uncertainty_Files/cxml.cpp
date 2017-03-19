#include "cxml.h"

CXml::CXml()
{
	doc=new TiXmlDocument();

	strtemp=NULL;
	currelem=NULL;
	rootelem=NULL; 

	return;
}

CXml::~CXml(){//��ֹ�ڴ�й¶
	if(strtemp!=NULL)
		delete(strtemp);
}

bool CXml::open(const char *filename)
{
	bool ok=false;
	if(doc->LoadFile(filename)){//�ɹ����ļ�
		rootelem=doc->RootElement();
		if(rootelem)//�ɹ�����׸�Ԫ��
			ok=true;
	}
	return ok;
}


char* CXml::readElementAttr(const char * element,const char * attribute,const char *parent)
{
	char *result=NULL;

	if(element==NULL||attribute==NULL)
		return result;

	//�����ָ�����ڵ�����ҵ����ڵ㣬Ȼ��Ӹ��ڵ㿪ʼ���ӽڵ�
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//�Ҳ������ڵ�
			return result;
	}
	if(findElement(rootelem,element,currelem)){
		int len=strlen(currelem->Attribute(attribute));//��ȡ�ı��ĳ���
		if(len){//����textֵ   
			result=new char[len+1];//�����ڴ�
			strcpy(result,currelem->Attribute(attribute));//�����ַ�����ֵ
			strtemp=result;//����ֵstrtextָ��ͬһ�ڴ�,��ֹ�ڴ�й¶ 
		}  
	} 
	rootelem=doc->RootElement();//�ָ������ڵ��ָ��Ϊ�ı��Ķ��ڵ�
	return result;
}

bool CXml::setElementAttr(const char * element,const char* attribute,const char* value,const char *parent)
{
	bool ok=false;
	if(element==NULL||attribute==NULL||value==NULL)
		return ok;
	//�����ָ�����ڵ�����ҵ����ڵ㣬Ȼ��Ӹ��ڵ㿪ʼ���ӽڵ�
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//�Ҳ������ڵ�
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		currelem->SetAttribute(attribute,value);
		ok=true;
	}  
	rootelem=doc->RootElement();//�ָ������ڵ��ָ��Ϊ�ı��Ķ��ڵ�
	doc->SaveFile();//�������

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
	//�����ָ�����ڵ�����ҵ����ڵ㣬Ȼ��Ӹ��ڵ㿪ʼ���ӽڵ�
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//�Ҳ������ڵ�
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		len=strlen(currelem->GetText());//��ȡ�ı��ĳ���
		if(len){//����textֵ   
			text=new char[len+1];//�����ڴ�
			strcpy(text,currelem->GetText());//�����ַ�����ֵ
			strtemp=text;//����ֵstrtextָ��ͬһ�ڴ�,��ֹ�ڴ�й¶ 
			ok=true;
		}  
	}
	rootelem=doc->RootElement();//�ָ������ڵ��ָ��Ϊ�ı��Ķ��ڵ�
	return ok;
}

bool CXml::setElementText(const char * element,const char* value,const char *parent)
{
	bool ok=false;
	if(element==NULL||parent==NULL||value==NULL)
		return ok;
	//�����ָ�����ڵ�����ҵ����ڵ㣬Ȼ��Ӹ��ڵ㿪ʼ���ӽڵ�
	if(parent!=NULL){
		if(findElement(rootelem,parent,currelem)){
			rootelem=currelem;
		}else//�Ҳ������ڵ�
			return ok;
	}
	if(findElement(rootelem,element,currelem)){
		currelem->ReplaceChild(currelem->FirstChild(),TiXmlText(value));
		ok=true;
	}  
	rootelem=doc->RootElement();//�ָ������ڵ��ָ��Ϊ�ı��Ķ��ڵ�
	doc->SaveFile();//�������

	return ok;
}


bool CXml::findElement(TiXmlElement* rootelem,const char *element,TiXmlElement* &node)
{
	bool ok=false;
	if(strcmp(element,rootelem->Value())==0){//�Ƚϵ�ǰԪ�ص����ƺ�Ҫ���ҵ�����
		node=rootelem;
		ok=true;
	}else{//û�ҵ�,�����ӽڵ�,�����ֵܽڵ�
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