#include "tinyxml.h"


class  CXml {
public:

	// TODO: add your methods here.

	//��ȡ��ȡָ��Ԫ��element��textֵ,�ҵ���Ԫ��,����true������*textָ���ֵ
	//û�и�Ԫ�أ�����false,textָ��ΪNULL
	//parentΪelementԪ�صĸ��ڵ�
	bool readElementText(const char * element,char * &text,const char *parent=NULL);

	//�趨ָ���ڵ�element��textֵΪvalue,parentΪ���ڵ�����
	//�趨�ɹ�����true
	bool setElementText(const char * element,const char* value,const char *parent=NULL);

	//��ȡָ��Ԫ��element��ָ�������Ե�����ֵ���ҵ�ʱ���ظ�����ֵ
	//û�и�Ԫ�ػ���ָ�����ԣ�����NULL
	//parentΪelementԪ�صĸ��ڵ�
	char* readElementAttr(const char * element,const char * attribute,const char *parent=NULL);

	//�趨ָ���ڵ�element��attributeֵΪvalue,parentΪ���ڵ�����
	//�趨�ɹ�����true
	bool setElementAttr(const char * element,const char* attribute,const char* value,const char *parent=NULL);

	bool open(const char* filename);

	CXml(void);
	~CXml(void);


	TiXmlDocument *doc;//XML�ļ�

	TiXmlElement *currelem;//XML�ڵ�Ԫ��,��ǰ�ڵ�Ԫ��
	TiXmlElement *rootelem;//XML�ڵ�Ԫ��,���ڵ�

	char* strtemp;

public:
	//���ļ�����Ԫ��rootelem��ʼ������Ϊelement��Ԫ��
	//�ҵ�ָ����Ԫ��,�ҵ�ʱ����true,fͬʱ����TiXmlElement���͵�Ҫ���ҵ�Ԫ��node
	bool findElement(TiXmlElement* rootelem,const char *element,TiXmlElement* &node);
	bool findElement(TiXmlElement* rootelem,const char *element,const char *attriname,const char *attrivalue,TiXmlElement* &node);


};