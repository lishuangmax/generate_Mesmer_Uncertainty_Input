
// Mesmer_Uncertainty_FilesDlg.cpp : 实现文件
//
// 20141124 update: deltaEDown 改为 deltaEDown_Prefactor,添加了help menu
// 20160107 update: 增加对Mesmer4.0输出文件的支持
// 20160324 update: 可以自己选择TP文件路径和名字,V4.94
// 201600530 update: bug 修复, loadConf时只能读取前11个参数,V4.9.5
// 201600922 update: bug 修复, 碰撞参数的指前因子的ID为0导致无法生成有效的input文件,V4.9.6

#include "stdafx.h"
#include "Mesmer_Uncertainty_Files.h"
#include "Mesmer_Uncertainty_FilesDlg.h"
#include "afxdialogex.h"
#include"cxml.h"
#include"tinyxml.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream> 
#include<random>
#include<math.h>
#include<boost/algorithm/string.hpp>
#include<regex>
#define _SCL_SECURE_NO_WARNINGS 
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpCopyright2014shuangli();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_HELP_COPYRIGHT2014SHUANGLI, &CAboutDlg::OnHelpCopyright2014shuangli)
END_MESSAGE_MAP()


// CMesmer_Uncertainty_FilesDlg 对话框



CMesmer_Uncertainty_FilesDlg::CMesmer_Uncertainty_FilesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMesmer_Uncertainty_FilesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMesmer_Uncertainty_FilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_filepath, filepath);
	DDX_Control(pDX, IDC_COMBO1, combo_moleculelist);
	DDX_Control(pDX, IDC_COMBO3, energy_unit);
	DDX_Control(pDX, IDC_COMBO4, vib_unit);
	DDX_Control(pDX, IDC_COMBO5, rot_unit);
	DDX_Control(pDX, IDC_COMBO6, image_unit);
	DDX_Control(pDX, IDC_COMBO2, delta_EDown);
	DDX_Control(pDX, IDC_COMBO7, sigma_unit);
	DDX_Control(pDX, IDC_COMBO8, epsilon_unit);
	DDX_Control(pDX, IDC_EDIT1, edit_energy);
	DDX_Control(pDX, IDC_EDIT2, edit_vib_num);
	DDX_Control(pDX, IDC_EDIT3, edit_vib);
	DDX_Control(pDX, IDC_EDIT4, edit_rot_num);
	DDX_Control(pDX, IDC_EDIT5, edit_rot);
	DDX_Control(pDX, IDC_EDIT6, edit_image);
	DDX_Control(pDX, IDC_EDIT7, edit_deltaEDown);
	DDX_Control(pDX, IDC_EDIT8, edit_sigma);
	DDX_Control(pDX, IDC_EDIT9, edit_epsilon);
	DDX_Control(pDX, IDC_CHECK1, select_energy);
	DDX_Control(pDX, IDC_CHECK2, select_vib);
	DDX_Control(pDX, IDC_CHECK3, select_rot);
	DDX_Control(pDX, IDC_CHECK4, select_image);
	DDX_Control(pDX, IDC_CHECK5, select_deltaEDown);
	DDX_Control(pDX, IDC_CHECK6, select_sigma);
	DDX_Control(pDX, IDC_CHECK7, select_epsilon);
	DDX_Control(pDX, IDC_EDIT10, sample_size);
	DDX_Control(pDX, IDC_STATIC_outpath, outpathname);
	DDX_Control(pDX, IDC_EDIT11, edit_p_num);
	DDX_Control(pDX, IDC_EDIT12, edit_mesmer_outfile_path);
	DDX_Control(pDX, IDC_EDIT13, edit_outfile_samplesize);
	DDX_Control(pDX, IDC_STATIC_state, static_run_state);
	DDX_Control(pDX, IDC_STATIC_mesinput, static_make_mesmer_input_state);
	DDX_Control(pDX, IDC_CHECK8, select_deltaEDownTE);
	DDX_Control(pDX, IDC_CHECK9, select_hinderedRotor);
	DDX_Control(pDX, IDC_EDIT14, edit_deltaEDownTE);
	DDX_Control(pDX, IDC_EDIT15, edit_hinderedRotor);
	DDX_Control(pDX, IDC_COMBO9, deltaEDownTE_unit);
	DDX_Control(pDX, IDC_COMBO10, hinderedRotor_unit);
	DDX_Control(pDX, IDC_COMBO11, combo_reactionlist);
	DDX_Control(pDX, IDC_CHECK10, select_preExponential);
	DDX_Control(pDX, IDC_EDIT16, edit_preExponential);
	DDX_Control(pDX, IDC_COMBO12, preExponential_unit);
	DDX_Control(pDX, IDC_CHECK11, select_Exponent);
	DDX_Control(pDX, IDC_EDITExponent, edit_Exponent);
	DDX_Control(pDX, IDC_COMBOExponentunit, Exponent_unit);
	DDX_Control(pDX, IDC_EDITSampleSizeMin, edit_outfile_sizeMin);
	DDX_Control(pDX, IDC_EDIT17, modifiedGrainSize);
	DDX_Control(pDX, IDC_BUTTON11, ModifiedSettings);
	DDX_Control(pDX, IDC_CHECK12, isModifyCondition);
	DDX_Control(pDX, IDC_BUTTON10, LoadConfig);
	DDX_Control(pDX, IDC_BUTTON12, buttonSaveRatePath);
	DDX_Control(pDX, IDC_STATIC_SavePath, editSavePath);
	DDX_Control(pDX, IDC_CHECK13, modifyGrainSize);
	DDX_Control(pDX, IDC_EDIT18, TP_FileName);
}

BEGIN_MESSAGE_MAP(CMesmer_Uncertainty_FilesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMesmer_Uncertainty_FilesDlg::OnBnClickedOpenFile)
	ON_BN_CLICKED(IDC_CHECK1, &CMesmer_Uncertainty_FilesDlg::OnBnClickedEnergySelect)
	ON_BN_CLICKED(IDC_CHECK2, &CMesmer_Uncertainty_FilesDlg::OnBnClickedVibSelect)
	ON_BN_CLICKED(IDC_CHECK3, &CMesmer_Uncertainty_FilesDlg::OnBnClickedRotSelect)
	ON_BN_CLICKED(IDC_CHECK4, &CMesmer_Uncertainty_FilesDlg::OnBnClickedImageSelect)
	ON_BN_CLICKED(IDC_CHECK5, &CMesmer_Uncertainty_FilesDlg::OnBnClickedDeltaEDownSelect)
	ON_BN_CLICKED(IDC_CHECK6, &CMesmer_Uncertainty_FilesDlg::OnBnClickedSigmaSelect)
	ON_BN_CLICKED(IDC_CHECK7, &CMesmer_Uncertainty_FilesDlg::OnBnClickedEpsilonSelect)
	ON_BN_CLICKED(IDC_BUTTON2, &CMesmer_Uncertainty_FilesDlg::OnBnClickedAddOneRecord)
	ON_BN_CLICKED(IDC_BUTTON3, &CMesmer_Uncertainty_FilesDlg::OnBnClickedCheckParameters)
	ON_BN_CLICKED(IDC_BUTTON4, &CMesmer_Uncertainty_FilesDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_BUTTON5, &CMesmer_Uncertainty_FilesDlg::OnBnClickedOutPath)
	ON_BN_CLICKED(IDC_BUTTON7, &CMesmer_Uncertainty_FilesDlg::OnBnClickedMesmerOutPath)
	ON_BN_CLICKED(IDC_BUTTON6, &CMesmer_Uncertainty_FilesDlg::OnBnClickedGetRateConstants)
	ON_BN_CLICKED(IDC_BUTTON8, &CMesmer_Uncertainty_FilesDlg::OnBnClickedRunRateConstant)
	ON_BN_CLICKED(IDC_CHECK8, &CMesmer_Uncertainty_FilesDlg::OnBnClickedDeltaTESelect)
	ON_BN_CLICKED(IDC_CHECK9, &CMesmer_Uncertainty_FilesDlg::OnBnClickedHinderedRotorSelect)
	ON_BN_CLICKED(IDC_CHECK10, &CMesmer_Uncertainty_FilesDlg::OnBnClickedpreExponentialSelect)
	ON_BN_CLICKED(IDC_BUTTON9, &CMesmer_Uncertainty_FilesDlg::OnBnClickedAddOneReactionRecord)
	ON_BN_CLICKED(IDC_CHECK11, &CMesmer_Uncertainty_FilesDlg::OnBnClickedExponentSelect)
	ON_COMMAND(ID_HELP_SLI, &CMesmer_Uncertainty_FilesDlg::OnHelpSli)
	ON_COMMAND(ID_HELP_COPYRIGHT2014SHUANGLI, &CMesmer_Uncertainty_FilesDlg::OnHelpCopyright2014shuangli)
	ON_BN_CLICKED(IDC_BUTTON11, &CMesmer_Uncertainty_FilesDlg::OnBnClickedButton1Modified)
	//ON_BN_CLICKED(IDC_CHECK12, &CMesmer_Uncertainty_FilesDlg::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_BUTTON10, &CMesmer_Uncertainty_FilesDlg::OnBnClickedButtonLoadConfig)
	ON_BN_CLICKED(IDC_BUTTON12, &CMesmer_Uncertainty_FilesDlg::OnBnClickedButtonSaveRatePath)
END_MESSAGE_MAP()


// CMesmer_Uncertainty_FilesDlg 消息处理程序

BOOL CMesmer_Uncertainty_FilesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	pMenu = new CMenu();
	pMenu->LoadMenu(IDR_MENU1);
	SetMenu(pMenu);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	energy_unit.AddString(_T("1"));
	energy_unit.AddString(_T("%"));
	energy_unit.SetCurSel(1);

	vib_unit.AddString(_T("1"));
	vib_unit.AddString(_T("%"));
	vib_unit.SetCurSel(0);

	rot_unit.AddString(_T("1"));
	rot_unit.AddString(_T("%"));
	rot_unit.SetCurSel(0);

	image_unit.AddString(_T("1"));
	image_unit.AddString(_T("%"));
	image_unit.SetCurSel(0);

	delta_EDown.AddString(_T("1"));
	delta_EDown.AddString(_T("%"));
	delta_EDown.SetCurSel(0);

	sigma_unit.AddString(_T("1"));
	sigma_unit.AddString(_T("%"));
	sigma_unit.SetCurSel(0);

	epsilon_unit.AddString(_T("1"));
	epsilon_unit.AddString(_T("%"));
	epsilon_unit.SetCurSel(0);

	deltaEDownTE_unit.AddString(_T("1"));
	deltaEDownTE_unit.AddString(_T("%"));
	deltaEDownTE_unit.SetCurSel(1);

	hinderedRotor_unit.AddString(_T("1"));
	hinderedRotor_unit.AddString(_T("%"));
	hinderedRotor_unit.SetCurSel(0);

	preExponential_unit.AddString(_T("1"));
	preExponential_unit.AddString(_T("%"));
	preExponential_unit.SetCurSel(0);

	Exponent_unit.AddString(_T("1"));
	Exponent_unit.AddString(_T("% multiple"));
	Exponent_unit.SetCurSel(1);

	select_energy.SetCheck(true);
	select_vib.SetCheck(true);
	select_rot.SetCheck(FALSE);
	select_preExponential.SetCheck(true);
	select_Exponent.SetCheck(true);

	select_image.SetCheck(FALSE);
	select_deltaEDown.SetCheck(FALSE);
	select_sigma.SetCheck(FALSE);
	select_epsilon.SetCheck(FALSE);

	edit_image.EnableWindow(FALSE);
	image_unit.EnableWindow(FALSE);

	edit_rot.EnableWindow(FALSE);
	rot_unit.EnableWindow(FALSE);
	edit_rot_num.EnableWindow(FALSE);

	edit_deltaEDown.EnableWindow(FALSE);
	delta_EDown.EnableWindow(FALSE);

	edit_sigma.EnableWindow(FALSE);
	sigma_unit.EnableWindow(FALSE);

	edit_epsilon.EnableWindow(FALSE);
	epsilon_unit.EnableWindow(FALSE);

	deltaEDownTE_unit.EnableWindow(FALSE);
	edit_deltaEDownTE.EnableWindow(FALSE);

	hinderedRotor_unit.EnableWindow(FALSE);
	edit_hinderedRotor.EnableWindow(FALSE);

	isModifyCondition.SetCheck(true);
	parameter_num = 0;
	modifyGrainSize.SetCheck(true);
	modifiedGrainSize.SetWindowTextW(_T("60"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMesmer_Uncertainty_FilesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMesmer_Uncertainty_FilesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMesmer_Uncertainty_FilesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMesmer_Uncertainty_FilesDlg::OnBnClickedOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog mFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,_T("Log Files (*.xml) | *.xml|*.XML|"),AfxGetMainWnd());
	if(mFileDlg.DoModal()==IDOK)
	{
		mollecule_attribute_uncertainty_flag.clear();
		mollecule_attribute_uncertainty_value.clear();
		reaction_attribute_uncertainty_flag.clear();
		reaction_attribute_uncertainty_value.clear();
		allmolecule.clear();
		allreaction.clear();
		combo_moleculelist.Clear();
		combo_reactionlist.Clear();
		combo_moleculelist.ResetContent();
		combo_reactionlist.ResetContent();

		FilePathName = mFileDlg.GetPathName();
		filepath.SetWindowTextW(FilePathName);
		string_filepathname = FilePathName;

		TiXmlDocument doc((char*)_bstr_t( ((wstring)(FilePathName.GetBuffer())).c_str()));
		doc.LoadFile();
		TiXmlElement *RootElement = doc.RootElement();
		TiXmlElement* moleculeListelment = RootElement->FirstChildElement("moleculeList");
		TiXmlElement* reactionListelment = RootElement->FirstChildElement("reactionList");
		TiXmlElement* tempElement;
		tempElement = moleculeListelment->FirstChildElement("molecule");          
		allmolecule.clear();
		allreaction.clear();
		while(tempElement)                           //获取所有分子
		{
			TiXmlAttribute* moleculeattribute = tempElement->FirstAttribute();
			string attributname = moleculeattribute->Value();
			allmolecule.push_back((CString)attributname.c_str());
			//	AfxMessageBox((CString)attributname.c_str());
			tempElement = tempElement->NextSiblingElement("molecule");
		}

		tempElement = reactionListelment->FirstChildElement("reaction");
		while (tempElement)                           //获取所有反应
		{
			TiXmlAttribute* reactionattribute = tempElement->FirstAttribute();
			string attributname = reactionattribute->Value();
			allreaction.push_back((CString)attributname.c_str());
			//	AfxMessageBox((CString)attributname.c_str());
			tempElement = tempElement->NextSiblingElement("reaction");
		}
		for (int i = 0;i<allmolecule.size();i++)
		{
			combo_moleculelist.AddString(allmolecule[i]);
		}
		for (int i = 0; i<allreaction.size(); i++)
		{
			combo_reactionlist.AddString(allreaction[i]);
		}
		combo_moleculelist.SetCurSel(0);
		combo_reactionlist.SetCurSel(0);
		
	}
	
	
	
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedEnergySelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_energy.GetCheck())
	{
		edit_energy.EnableWindow(FALSE);
		energy_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_energy.EnableWindow(TRUE);
		energy_unit.EnableWindow(TRUE);
	}
	
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedVibSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_vib.GetCheck())
	{
		edit_vib.EnableWindow(FALSE);
		edit_vib_num.EnableWindow(FALSE);
		vib_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_vib.EnableWindow(TRUE);
		edit_vib_num.EnableWindow(TRUE);
		vib_unit.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedRotSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_rot.GetCheck())
	{
		edit_rot.EnableWindow(FALSE);
		edit_rot_num.EnableWindow(FALSE);
		rot_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_rot.EnableWindow(TRUE);
		edit_rot_num.EnableWindow(TRUE);
		rot_unit.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedImageSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_image.GetCheck())
	{
		edit_image.EnableWindow(FALSE);
		image_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_image.EnableWindow(TRUE);
		image_unit.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedDeltaEDownSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_deltaEDown.GetCheck())
	{
		edit_deltaEDown.EnableWindow(FALSE);
		delta_EDown.EnableWindow(FALSE);
	}
	else
	{
		edit_deltaEDown.EnableWindow(TRUE);
		delta_EDown.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedSigmaSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_sigma.GetCheck())
	{
		edit_sigma.EnableWindow(FALSE);
		sigma_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_sigma.EnableWindow(TRUE);
		sigma_unit.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedEpsilonSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!select_epsilon.GetCheck())
	{
		edit_epsilon.EnableWindow(FALSE);
		epsilon_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_epsilon.EnableWindow(TRUE);
		epsilon_unit.EnableWindow(TRUE);
	}
}

void CMesmer_Uncertainty_FilesDlg::OnBnClickedDeltaTESelect()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!select_deltaEDownTE.GetCheck())
	{
		edit_deltaEDownTE.EnableWindow(FALSE);
		deltaEDownTE_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_deltaEDownTE.EnableWindow(TRUE);
		deltaEDownTE_unit.EnableWindow(TRUE);
	}
}

void CMesmer_Uncertainty_FilesDlg::OnBnClickedHinderedRotorSelect()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!select_hinderedRotor.GetCheck())
	{
		edit_hinderedRotor.EnableWindow(FALSE);
		hinderedRotor_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_hinderedRotor.EnableWindow(TRUE);
		hinderedRotor_unit.EnableWindow(TRUE);
	}
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedpreExponentialSelect()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!select_preExponential.GetCheck())
	{
		edit_preExponential.EnableWindow(FALSE);
		preExponential_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_preExponential.EnableWindow(TRUE);
		preExponential_unit.EnableWindow(TRUE);
	}
}

void CMesmer_Uncertainty_FilesDlg::OnBnClickedExponentSelect()
{
	if (!select_Exponent.GetCheck())
	{
		edit_Exponent.EnableWindow(FALSE);
		Exponent_unit.EnableWindow(FALSE);
	}
	else
	{
		edit_Exponent.EnableWindow(TRUE);
		Exponent_unit.EnableWindow(TRUE);
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedAddOneRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	bool right_flag = true;
	CString select_molecule_name;
	map<string, bool> temp_attribute_flag;
	map<string, vector<double>> temp_attribute_value;
	vector<double> temp_one_attribute_value;         //第一个值表示数据形式，0表示%,  1表示 1，第二个表示参数个数，后面的值表示参数值
	combo_moleculelist.GetWindowTextW(select_molecule_name);

	if (select_molecule_name.IsEmpty())
	{
		AfxMessageBox(_T("未选中物种"));
	}
	else
	{
		if (select_energy.GetCheck())    //获取能量相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			energy_unit.GetWindowTextW(temp_unit);
			edit_energy.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("能量值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			/*	for (int i = 0;i<temp_one_attribute_value.size();i++)
				{
				outfile<<temp_one_attribute_value[i]<<"	";
				}
				*/
			temp_attribute_value.insert(make_pair("energy", temp_one_attribute_value));
			//		outfile.close();
		}

		if (select_vib.GetCheck())    //获取振动频率相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value, value_num;
			CString temp_unit, temp_value_string, temp_value_num_string;
			vector<string> split_value_string;
			vector<double>vib_value;
			vib_unit.GetWindowTextW(temp_unit);
			edit_vib.GetWindowTextW(temp_value_string);
			edit_vib_num.GetWindowTextW(temp_value_num_string);

			string string_vaule = (char*)_bstr_t(((wstring)(temp_value_string.GetBuffer())).c_str());
			boost::split(split_value_string, string_vaule, boost::is_any_of(" "), boost::token_compress_on);
			if (split_value_string[0].empty())
			{
				split_value_string.erase(split_value_string.begin());
			}
			if (split_value_string[split_value_string.size() - 1].empty())
			{
				split_value_string.erase(split_value_string.end() - 1);
			}
			for (int i = 0; i < split_value_string.size(); i++)
			{
				string tempstring = split_value_string[i];
				boost::trim(tempstring);
				split_value_string[i] = tempstring;
			}
			//		outfile<<split_value_string.size()<<endl;
			//		AfxMessageBox(temp_value_string);
			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}

			if (temp_value_num_string != "")
			{
				value_num = _ttof(temp_value_num_string);
				temp_one_attribute_value.push_back(value_num);
			}
			else
			{
				AfxMessageBox(_T("振动频率个数不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_value_string != "")
			{
				if (split_value_string.size() == value_num)
				{
					for (int i = 0; i < split_value_string.size(); i++)
					{
						temp_value = atof(split_value_string[i].c_str());
						temp_one_attribute_value.push_back(temp_value);
					}
				}
				else
				{
					AfxMessageBox(_T("输入的振动频率个数和设置个数不相等，请认真检查"));
					right_flag = false;
					exit;
				}


			}
			else
			{
				AfxMessageBox(_T("振动频率值不能为空"));
				right_flag = false;
				exit;
			}

			temp_attribute_value.insert(make_pair("vib", temp_one_attribute_value));

		}

		if (select_rot.GetCheck())    //获取转动频率相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value, value_num;
			CString temp_unit, temp_value_string, temp_value_num_string;
			vector<string> split_value_string;
			vector<double>rot_value;
			rot_unit.GetWindowTextW(temp_unit);
			edit_rot.GetWindowTextW(temp_value_string);
			edit_rot_num.GetWindowTextW(temp_value_num_string);

			string string_vaule = (char*)_bstr_t(((wstring)(temp_value_string.GetBuffer())).c_str());
			boost::split(split_value_string, string_vaule, boost::is_any_of(" "), boost::token_compress_on);
			if (split_value_string[0].empty())
			{
				split_value_string.erase(split_value_string.begin());
			}
			if (split_value_string[split_value_string.size() - 1].empty())
			{
				split_value_string.erase(split_value_string.end() - 1);
			}
			for (int i = 0; i < split_value_string.size(); i++)
			{
				string tempstring = split_value_string[i];
				boost::trim(tempstring);
				split_value_string[i] = tempstring;
			}
			//		outfile<<split_value_string.size()<<endl;
			//		AfxMessageBox(temp_value_string);
			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}

			if (temp_value_num_string != "")
			{
				value_num = _ttof(temp_value_num_string);
				temp_one_attribute_value.push_back(value_num);
			}
			else
			{
				AfxMessageBox(_T("转动频率个数不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_value_string != "")
			{
				if (split_value_string.size() == value_num)
				{
					for (int i = 0; i < split_value_string.size(); i++)
					{
						temp_value = atof(split_value_string[i].c_str());
						temp_one_attribute_value.push_back(temp_value);
					}
				}
				else
				{
					AfxMessageBox(_T("输入的振动频率个数和设置个数不相等，请认真检查"));
					right_flag = false;
					exit;
				}

			}
			else
			{
				AfxMessageBox(_T("转动频率值不能为空"));
				right_flag = false;
				exit;
			}

			temp_attribute_value.insert(make_pair("rot", temp_one_attribute_value));

		}
		if (select_image.GetCheck())    //获取虚频相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			image_unit.GetWindowTextW(temp_unit);
			edit_image.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("虚频值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("image", temp_one_attribute_value));
		}
		if (select_deltaEDown.GetCheck())    //获取deltaEDown相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			delta_EDown.GetWindowTextW(temp_unit);
			edit_deltaEDown.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("deltaEDown值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("deltaEDown_Prefactor", temp_one_attribute_value));
		}
		if (select_sigma.GetCheck())    //获取sigma相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			sigma_unit.GetWindowTextW(temp_unit);
			edit_sigma.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("sigma值不能为空"));
				right_flag = false;
				exit;
			}

			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("sigma", temp_one_attribute_value));
		}
		if (select_epsilon.GetCheck())    //获取epsilon相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			epsilon_unit.GetWindowTextW(temp_unit);
			edit_epsilon.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("epsilon 值不能为空"));
				right_flag = false;
				exit;
			}

			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("epsilon", temp_one_attribute_value));
		}
		if (select_deltaEDownTE.GetCheck())    //获取deltaEDownTE相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			deltaEDownTE_unit.GetWindowTextW(temp_unit);
			edit_deltaEDownTE.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("deltaEDownTE值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("deltaEDownTE", temp_one_attribute_value));
		}
		if (select_hinderedRotor.GetCheck())    //获取hinderedRotor相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			hinderedRotor_unit.GetWindowTextW(temp_unit);
			edit_hinderedRotor.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("hinderedRotor值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("hinderedRotor", temp_one_attribute_value));
		}
	}
	if (right_flag == true)
	{
		auto insert_state = mollecule_attribute_uncertainty_value.insert(make_pair((string)(char*)_bstr_t(((wstring)(select_molecule_name.GetBuffer())).c_str()), temp_attribute_value));
		if (insert_state.second)
		{
			AfxMessageBox(_T("添加成功"));
		}
		else
		{

			mollecule_attribute_uncertainty_value.erase((string)(char*)_bstr_t(((wstring)(select_molecule_name.GetBuffer())).c_str()));
			mollecule_attribute_uncertainty_value.insert(make_pair((string)(char*)_bstr_t(((wstring)(select_molecule_name.GetBuffer())).c_str()), temp_attribute_value));
			AfxMessageBox(select_molecule_name + _T(" 的参数信息已存在, 将覆盖原有信息"));
		}
	}

}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedAddOneReactionRecord()   //添加要分析的反应属性
{
	// TODO:  在此添加控件通知处理程序代码
	bool right_flag = true;
	CString select_reaction_name;
	map<string, bool> temp_attribute_flag;
	map<string, vector<double>> temp_attribute_value;
	vector<double> temp_one_attribute_value;         //第一个值表示数据形式，0表示%,  1表示 1，第二个表示参数个数，后面的值表示参数值
	combo_reactionlist.GetWindowTextW(select_reaction_name);

	if (select_reaction_name.IsEmpty())
	{
		AfxMessageBox(_T("未选中反应"));
	}
	else
	{

		if (select_preExponential.GetCheck())    //获取deltaEDownTE相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			preExponential_unit.GetWindowTextW(temp_unit);
			edit_preExponential.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);
			}
			else
			{
				AfxMessageBox(_T("preExponential值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("preExponential", temp_one_attribute_value));
		}

		if (select_Exponent.GetCheck())    //获取deltaEDownTE相关信息
		{
			temp_one_attribute_value.clear();
			double temp_value;
			CString temp_unit, temp_value_string;
			Exponent_unit.GetWindowTextW(temp_unit);
			edit_Exponent.GetWindowTextW(temp_value_string);
			if (temp_value_string != "")
			{
				temp_value = _ttof(temp_value_string);		
			}
			else
			{
				AfxMessageBox(_T("activationEnergy 值不能为空"));
				right_flag = false;
				exit;
			}


			if (temp_unit == "%")
			{
				temp_one_attribute_value.push_back(0);
			}
			else
			{
				temp_one_attribute_value.push_back(1);
			}
			temp_one_attribute_value.push_back(1);
			temp_one_attribute_value.push_back(temp_value);

			temp_attribute_value.insert(make_pair("activationEnergy", temp_one_attribute_value));
		}
		
	}
	if (right_flag == true)
	{
		auto insert_state = reaction_attribute_uncertainty_value.insert(make_pair((string)(char*)_bstr_t(((wstring)(select_reaction_name.GetBuffer())).c_str()), temp_attribute_value));
		if (insert_state.second)
		{
			AfxMessageBox(_T("添加成功"));
		}
		else
		{

			reaction_attribute_uncertainty_value.erase((string)(char*)_bstr_t(((wstring)(select_reaction_name.GetBuffer())).c_str()));
			reaction_attribute_uncertainty_value.insert(make_pair((string)(char*)_bstr_t(((wstring)(select_reaction_name.GetBuffer())).c_str()), temp_attribute_value));
			AfxMessageBox(select_reaction_name + _T(" 的参数信息已存在, 将覆盖原有信息"));
		}
	}

}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedCheckParameters()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream out_parameters("parameters.dat");
	map<string,vector<double>> oneMoleculeAttribute;
	vector<double> oneAttribute;
	for (auto iter = mollecule_attribute_uncertainty_value.cbegin();iter != mollecule_attribute_uncertainty_value.cend();iter++)
	{		
		
		out_parameters<<iter->first<<endl;
		oneMoleculeAttribute = iter->second;
		for (auto iterone = oneMoleculeAttribute.cbegin(); iterone != oneMoleculeAttribute.cend();iterone++)  //以分子形式展示参数
		{
			out_parameters<<iterone->first<<"	";
			oneAttribute = iterone->second;
			for (int i = 2;i<oneAttribute.size();i++)
			{
				if (oneAttribute[0]==0)
				{
					out_parameters<<"±"<<oneAttribute[i]<<"%"<<"	";
				}
				else
				{
					out_parameters<<"±"<<oneAttribute[i]<<"	";
				}
			}
			out_parameters<<endl;
		}

		
	}
	for (auto iter = reaction_attribute_uncertainty_value.cbegin(); iter != reaction_attribute_uncertainty_value.cend(); iter++)
	{

		out_parameters << iter->first << endl;
		oneMoleculeAttribute = iter->second;
		for (auto iterone = oneMoleculeAttribute.cbegin(); iterone != oneMoleculeAttribute.cend(); iterone++)  //以分子形式展示参数
		{
			out_parameters << iterone->first << "	";
			oneAttribute = iterone->second;
			for (int i = 2; i<oneAttribute.size(); i++)
			{
				if (oneAttribute[0] == 0)
				{
					out_parameters << "±" << oneAttribute[i] << "%" << "	";
				}
				else
				{
					out_parameters << "±" << oneAttribute[i] << "	";
				}
			}
			out_parameters << endl;
		}


	}

	int p_num=0;    //参数序号
	out_parameters<<endl;
	CString showstring=CString("");
	for (auto iter = mollecule_attribute_uncertainty_value.cbegin();iter != mollecule_attribute_uncertainty_value.cend();iter++)
	{	
		oneMoleculeAttribute = iter->second;
		for (auto iterone = oneMoleculeAttribute.cbegin(); iterone != oneMoleculeAttribute.cend();iterone++)  //以参数列表形式展示参数
		{
			oneAttribute = iterone->second;
			for (int i = 2;i<oneAttribute.size();i++)
			{
				string ostring;
				ostringstream ostr,ostr1;
				ostr << (p_num + 1);
				ostr1 << oneAttribute[i];
				if (oneAttribute[0]==0)
				{
					out_parameters<<++p_num<<"	"<<iter->first<<"	"<<iterone->first<<"	±"<<oneAttribute[i]<<"%"<<endl;
					if (p_num<40)
					{				
						showstring = showstring + (CString)ostr.str().c_str() + _T("	") + (CString)(iter->first).c_str() + _T("	") + (CString)(iterone->first).c_str() + _T("	±") + (CString)(ostr1.str()).c_str() + _T("%\n");
					}
				}
				else
				{
					out_parameters<<++p_num<<"	"<<iter->first<<"	"<<iterone->first<<"	±"<<oneAttribute[i]<<endl;
//					showstring +=  (ostr.str + "	" + iter->first + "	" +iterone->first + "	±" + ostr1.str +"\n").c_str();
					if (p_num<40)
					{	
						showstring = showstring + (CString)ostr.str().c_str() + _T("	") + (CString)(iter->first).c_str() + _T("	") + (CString)(iterone->first).c_str() + _T("	±") + (CString)(ostr1.str()).c_str() + _T("\n");
					}

				}
				
			}
		}
	}
	for (auto iter = reaction_attribute_uncertainty_value.cbegin(); iter != reaction_attribute_uncertainty_value.cend(); iter++)
	{
		oneMoleculeAttribute = iter->second;
		for (auto iterone = oneMoleculeAttribute.cbegin(); iterone != oneMoleculeAttribute.cend(); iterone++)  //以参数列表形式展示参数
		{
			oneAttribute = iterone->second;
			for (int i = 2; i<oneAttribute.size(); i++)
			{
				string ostring;
				ostringstream ostr, ostr1;
				ostr << (p_num + 1);
				ostr1 << oneAttribute[i];
				if (oneAttribute[0] == 0)
				{
					out_parameters << ++p_num << "	" << iter->first << "	" << iterone->first << "	±" << oneAttribute[i] << "%" << endl;
					if (p_num<40)
					{
						showstring = showstring + (CString)ostr.str().c_str() + _T("	") + (CString)(iter->first).c_str() + _T("	") + (CString)(iterone->first).c_str() + _T("	±") + (CString)(ostr1.str()).c_str() + _T("%\n");
					}
				}
				else
				{
					out_parameters << ++p_num << "	" << iter->first << "	" << iterone->first << "	±" << oneAttribute[i] << endl;
					//					showstring +=  (ostr.str + "	" + iter->first + "	" +iterone->first + "	±" + ostr1.str +"\n").c_str();
					if (p_num<40)
					{
						showstring = showstring + (CString)ostr.str().c_str() + _T("	") + (CString)(iter->first).c_str() + _T("	") + (CString)(iterone->first).c_str() + _T("	±") + (CString)(ostr1.str()).c_str() + _T("\n");
					}

				}

			}
		}
	}

	out_parameters.close();
	if (p_num<40)
	{
		AfxMessageBox(showstring + _T("\n参数列表已保存到 parameters.dat 中"));
	}
	else
	{
		AfxMessageBox(showstring + _T("\n参数过多，只显示部分参数，详细参数列表已保存到 parameters.dat 中"));
	}
	
}

template<class T>
void CMesmer_Uncertainty_FilesDlg::alterinput(string xmlFileName,string inputdatafile,string inputfilename,T gen)        //转换成mesmer输入文件的文件名
{
	ofstream indatafile,parametersfile;
	indatafile.open(inputdatafile,ios::app);
	indatafile.setf(ios::fixed, ios::floatfield);
	indatafile.precision(10);
	parametersfile.open("Original_parameters.dat",ios::app);
//	parametersfile.setf(ios::fixed, ios::floatfield);
//	parametersfile.precision(10);
	

	map<string,vector<double>> oneMoleculeAttribute;
	map<string, vector<double>> oneReactionAttribute;
	string moleculename,reactionname;

	TiXmlDocument doc(xmlFileName.c_str());
	doc.LoadFile();
	TiXmlElement *RootElement = doc.RootElement();
	TiXmlElement* moleculeListelment = RootElement->FirstChildElement("moleculeList");
	TiXmlElement* reactionListelment = RootElement->FirstChildElement("reactionList");
	CXml cxml;
	cxml.rootelem = RootElement;
	cxml.currelem = moleculeListelment;
	cxml.doc = &doc;
	long double randtemp,randtemp0;
	TiXmlElement* moleculeElment;
	TiXmlElement* reactionElment;
	TiXmlElement* moleculePropertyListEmlent;
	TiXmlElement* moleculeAttributeElement;
	TiXmlElement* moleculeAttributeValueElement;
	TiXmlElement* reactionAttributeValueElement;
	TiXmlElement* moleculeExtraDOSCMethodElement;
	TiXmlElement* moleculeHinderedRotorPotentialElement;
	TiXmlElement* PotentialPointElement;
	for (auto itermolecule = mollecule_attribute_uncertainty_value.cbegin(); itermolecule != mollecule_attribute_uncertainty_value.cend(); itermolecule++)
	{
		moleculename = itermolecule->first;
		oneMoleculeAttribute = itermolecule->second;

		cxml.findElement(moleculeListelment, "molecule", "id", moleculename.c_str(), moleculeElment);          //找到分子
		cxml.findElement(moleculeElment, "propertyList", moleculePropertyListEmlent);
		
		for (auto iterattribute = oneMoleculeAttribute.cbegin(); iterattribute != oneMoleculeAttribute.cend(); iterattribute++)
		{
			string attributeName = iterattribute->first;
			vector<double> attributevalue = iterattribute->second;


			if (attributeName == "energy")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "Energy", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("scalar");
					string string_energy_orignal = moleculeAttributeValueElement->GetText();
					long double energyvalue_original = atof(string_energy_orignal.c_str());
					string string_energy;
					long double energyvalue;


					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
					//	energyvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*energyvalue_original;
						energyvalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2-1))*energyvalue_original;
					}
					else
					{
						energyvalue = energyvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrenergy;
					string str_energy;
					ostrenergy << energyvalue;
					str_energy = ostrenergy.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_energy.c_str());

					indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
					parametersfile << energyvalue << "	";   //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 Energy"));
					exit;
				}

			}        //end of energy
			else if (attributeName == "vib")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "Vibrational Frequencies", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("array");
					string string_vib_orignal = moleculeAttributeValueElement->GetText();           //所有振动频率在一起的一个字符串
					vector<string> split_string_vib_origianl;                                     //原始振动频率
					vector<string> split_string_vib_rand;                                        //修改后的振动频率
					vector<double> split_value_vib_original;                                    //将需要修改的振动频率转换成double型
					string allVibAlter;
					boost::trim(string_vib_orignal);
					boost::split(split_string_vib_origianl, string_vib_orignal, boost::is_any_of(" "), boost::token_compress_on);
					split_string_vib_rand = split_string_vib_origianl;
					double vibvalue;
					for (int i = 0; i < attributevalue[1]; i++)
					{
						string tempvibstring = split_string_vib_origianl[i];
						split_value_vib_original.push_back(atof(tempvibstring.c_str()));
					}

					if (attributevalue[0] == 0)
					{
						for (int i = 0; i < attributevalue[1]; i++)
						{
							randtemp0 = gen();
					//		vibvalue = (1 - attributevalue[i + 2] / 100 + randtemp0 * 2 * attributevalue[i + 2] / 100)*split_value_vib_original[i];
							vibvalue = pow((1 + attributevalue[i + 2] / 100), (randtemp0 * 2 - 1))*split_value_vib_original[i];
							ostringstream ostrvib;
							string str_vib;
							ostrvib << vibvalue;
							str_vib = ostrvib.str();
							split_string_vib_rand[i] = str_vib;

							indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
							parametersfile << vibvalue << "	";   //对应的参数值
						}
					}
					else
					{
						for (int i = 0; i < attributevalue[1]; i++)
						{

							randtemp0 = gen();

							vibvalue = split_value_vib_original[i] - attributevalue[i + 2] + randtemp0 * 2 * attributevalue[i + 2];

							ostringstream ostrvib;
							string str_vib;
							ostrvib << vibvalue;
							str_vib = ostrvib.str();

							split_string_vib_rand[i] = str_vib;

							indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
							parametersfile << vibvalue << "	";   //对应的参数值
						}
					}
					for (int i = 0; i < split_string_vib_rand.size(); i++)
					{
						allVibAlter += split_string_vib_rand[i] + " ";
					}

					moleculeAttributeValueElement->FirstChild()->SetValue(allVibAlter.c_str());
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 Vibrational Frequencies"));
					exit;
				}


			}                     //end of vib
			else if (attributeName == "rot")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "Rotational Constants", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("array");
					string string_rot_orignal = moleculeAttributeValueElement->GetText();           //所有转动频率在一起的一个字符串
					vector<string> split_string_rot_origianl;                                     //原始转动频率
					vector<string> split_string_rot_rand;                                        //修改后的转动频率
					vector<double> split_value_rot_original;                                    //将需要修改的转动频率转换成double型
					string allRotAlter;
					boost::trim(string_rot_orignal);
					boost::split(split_string_rot_origianl, string_rot_orignal, boost::is_any_of(" "), boost::token_compress_on);
					split_string_rot_rand = split_string_rot_origianl;
					double rotvalue;
					for (int i = 0; i < attributevalue[1]; i++)
					{
						string tempvibstring = split_string_rot_origianl[i];
						split_value_rot_original.push_back(atof(tempvibstring.c_str()));
					}

					if (attributevalue[0] == 0)
					{
						for (int i = 0; i < attributevalue[1]; i++)
						{
							randtemp0 = gen();
						//	rotvalue = (1 - attributevalue[i + 2] / 100 + randtemp0 * 2 * attributevalue[i + 2] / 100)*split_value_rot_original[i];
							rotvalue = pow((1 + attributevalue[i + 2] / 100), (randtemp0 * 2 - 1))*split_value_rot_original[i];
							ostringstream ostrrot;
							string str_rot;
							ostrrot << rotvalue;
							str_rot = ostrrot.str();
							split_string_rot_rand[i] = str_rot;

							indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
							parametersfile << rotvalue << "	";   //对应的参数值
						}
					}
					else
					{
						for (int i = 0; i < attributevalue[1]; i++)
						{

							randtemp0 = gen();
							rotvalue = split_value_rot_original[i] - attributevalue[i + 2] + randtemp0 * 2 * attributevalue[i + 2];

							ostringstream ostrrot;
							string str_rot;
							ostrrot << rotvalue;
							str_rot = ostrrot.str();
							split_string_rot_rand[i] = str_rot;

							indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
							parametersfile << rotvalue << "	";    //对应的参数值
						}
					}
					for (int i = 0; i < split_string_rot_rand.size(); i++)
					{
						allRotAlter += split_string_rot_rand[i] + " ";
					}

					moleculeAttributeValueElement->FirstChild()->SetValue(allRotAlter.c_str());
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 Rotational Constants"));
					exit;
				}

			}                     //end of rot
			else if (attributeName == "image")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "image Frequencies", moleculeAttributeElement))  //找到属性
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("array");
					string string_image_orignal = moleculeAttributeValueElement->GetText();
					long double imagevalue_original = atof(string_image_orignal.c_str());
					string string_image;
					long double imagevalue;



					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
					//	imagevalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*imagevalue_original;
						imagevalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*imagevalue_original;
					}
					else
					{
						imagevalue = imagevalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrimage;
					string str_image;
					ostrimage << imagevalue;
					str_image = ostrimage.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_image.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << imagevalue << "	";    //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 image Frequencies"));
					exit;
				}


			}        //end of image
			else if (attributeName == "deltaEDown_Prefactor")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "deltaEDown", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("scalar");
					string string_deltaEDown_orignal = moleculeAttributeValueElement->GetText();
					long double deltaEDownvalue_original = atof(string_deltaEDown_orignal.c_str());
					string string_deltaEDown;
					long double deltaEDownvalue;



					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
					//	deltaEDownvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*deltaEDownvalue_original;
						deltaEDownvalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*deltaEDownvalue_original;
					}
					else
					{
						deltaEDownvalue = deltaEDownvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}


					ostringstream ostrdeltaEDown;
					string str_deltaEDown;
					ostrdeltaEDown << deltaEDownvalue;
					str_deltaEDown = ostrdeltaEDown.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_deltaEDown.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << deltaEDownvalue << "	";   //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 deltaEDown"));
					exit;
				}

			}        //end of deltaEDown
			else if (attributeName == "sigma")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "sigma", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("scalar");
					string string_sigma_orignal = moleculeAttributeValueElement->GetText();
					long double sigmavalue_original = atof(string_sigma_orignal.c_str());
					string string_sigma;
					long double sigmavalue;



					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
					//	sigmavalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*sigmavalue_original;
						sigmavalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*sigmavalue_original;
					}
					else
					{
						sigmavalue = sigmavalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrsigma;
					string str_sigma;
					ostrsigma << sigmavalue;
					str_sigma = ostrsigma.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_sigma.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << sigmavalue << "	";   //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 sigma"));
					exit;
				}

			}        //end of sigma
			else if (attributeName == "epsilon")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "epsilon", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("scalar");
					string string_epsilon_orignal = moleculeAttributeValueElement->GetText();
					long double epsilonvalue_original = atof(string_epsilon_orignal.c_str());
					string string_epsilon;
					long double epsilonvalue;

					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
					//	epsilonvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*epsilonvalue_original;
						epsilonvalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*epsilonvalue_original;
					}
					else
					{
						epsilonvalue = epsilonvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrepsilon;
					string str_epsilon;
					ostrepsilon << epsilonvalue;
					str_epsilon = ostrepsilon.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_epsilon.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << epsilonvalue << "	";   //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 epsilon"));
					exit(0);
				}

			}        //end of epsilon
			else if (attributeName == "deltaEDownTE")
			{
				if (cxml.findElement(moleculePropertyListEmlent, "property", "title", "deltaEDownTExponent", moleculeAttributeElement))
				{
					moleculeAttributeValueElement = moleculeAttributeElement->FirstChildElement("scalar");
					string string_deltaEDownTE_orignal = moleculeAttributeValueElement->GetText();
					long double deltaEDownTEvalue_original = atof(string_deltaEDownTE_orignal.c_str());
					string string_deltaEDownTE;
					long double deltaEDownTEvalue;

					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
				//		deltaEDownTEvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*deltaEDownTEnvalue_original;
						deltaEDownTEvalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*deltaEDownTEvalue_original;
					}
					else
					{
						deltaEDownTEvalue = deltaEDownTEvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrdeltaEDownTE;
					string str_deltaEDownTE;
					ostrdeltaEDownTE << deltaEDownTEvalue;
					str_deltaEDownTE = ostrdeltaEDownTE.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_deltaEDownTE.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << deltaEDownTEvalue << "	";   //对应的参数值
				}
				else
				{
					AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 deltaEDownTE"));
					exit(0);
				}

			}        //end of deltaEDownTE
			else if (attributeName == "hinderedRotor")
			{
			//	if (cxml.findElement(moleculeElment, "property", "title", "deltaEDownTExponent", moleculeAttributeElement))
			//	{
				moleculeExtraDOSCMethodElement = moleculeElment->FirstChildElement("me:ExtraDOSCMethod");
				moleculeHinderedRotorPotentialElement = moleculeExtraDOSCMethodElement->FirstChildElement("me:HinderedRotorPotential");
				PotentialPointElement = moleculeHinderedRotorPotentialElement->FirstChildElement("me:PotentialPoint");
				randtemp0 = gen();
				long double hinderedRotorvalue;
				while (PotentialPointElement)
				{
					ostringstream ostrhinderedRotor;
					string str_hinderedRotor;
					string coefficientstring = PotentialPointElement->Attribute("coefficient");
					long double coefficientvalue = stof(coefficientstring.c_str());

					if (attributevalue[0] == 0)
					{
					//	hinderedRotorvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*coefficientvalue;
						hinderedRotorvalue = pow((1 + attributevalue[2] / 100), (randtemp0 * 2 - 1))*coefficientvalue;
					}
					else
					{
						hinderedRotorvalue = coefficientvalue - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostrhinderedRotor << hinderedRotorvalue;
					str_hinderedRotor = ostrhinderedRotor.str();
					
					PotentialPointElement->SetAttribute("coefficient", str_hinderedRotor.c_str());
					PotentialPointElement = PotentialPointElement->NextSiblingElement();
				}
				indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
				parametersfile << hinderedRotorvalue << "	";   //对应的参数值

				/*	string string_epsilon_orignal = moleculeAttributeValueElement->GetText();
					long double epsilonvalue_original = atof(string_epsilon_orignal.c_str());
					string string_epsilon;
					long double epsilonvalue;

					randtemp0 = gen();
					if (attributevalue[0] == 0)
					{
						epsilonvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*epsilonvalue_original;
					}
					else
					{
						epsilonvalue = epsilonvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
					}

					ostringstream ostrepsilon;
					string str_epsilon;
					ostrepsilon << epsilonvalue;
					str_epsilon = ostrepsilon.str();
					moleculeAttributeValueElement->FirstChild()->SetValue(str_epsilon.c_str());

					indatafile << randtemp0 << "	";      //数据写入HDMR输入文件
					parametersfile << epsilonvalue << "	";   //对应的参数值
					*/
			//	}
		//		else
		//		{
		//			AfxMessageBox(_T("物种 ") + (CString)moleculename.c_str() + _T(" 找不到属性 HinderedRotorPotential"));
		//			exit;
		//		}

			}        //end of HinderedRotorPotential
		}            //end of for moleculelist
		
	}
	for (auto iterreaction = reaction_attribute_uncertainty_value.cbegin(); iterreaction != reaction_attribute_uncertainty_value.cend(); iterreaction++)
	{
		reactionname = iterreaction->first;
		oneReactionAttribute = iterreaction->second;
		cxml.findElement(reactionListelment, "reaction", "id", reactionname.c_str(), reactionElment);          //找到反应
		//	cxml.findElement(moleculeElment, "propertyList", moleculePropertyListEmlent);
		for (auto iterattribute = oneReactionAttribute.cbegin(); iterattribute != oneReactionAttribute.cend(); iterattribute++)
		{
			string attributeName = iterattribute->first;
			vector<double> attributevalue = iterattribute->second;
			if (attributeName == "preExponential")        // lognornal 分布，取对数之后均匀取值
			{
				reactionAttributeValueElement = reactionElment->FirstChildElement("me:preExponential");
				string string_preExponential_orignal = reactionAttributeValueElement->GetText();
				long double preExponentialvalue_original = atof(string_preExponential_orignal.c_str());
				string string_preExponential;
				long double preExponentialvalue;


				randtemp0 = gen();
				if (attributevalue[0] == 0)
				{
					//preExponentialvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*preExponentialvalue_original;
					long double LnA;            //取ln之后的值
					LnA = log(preExponentialvalue_original) - log((attributevalue[2] / 100) + 1) + 2*log((attributevalue[2] / 100) + 1)*randtemp0;
					preExponentialvalue = exp(LnA);
				}
				else
				{
					preExponentialvalue = preExponentialvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
				}

				ostringstream ostrpreExponential;
				string str_preExponential;
				ostrpreExponential << preExponentialvalue;
				str_preExponential = ostrpreExponential.str();
				reactionAttributeValueElement->FirstChild()->SetValue(str_preExponential.c_str());


				indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
				parametersfile << preExponentialvalue << "	";   //对应的参数值


			}      //end of energy
			else if (attributeName == "activationEnergy")
			{
				reactionAttributeValueElement = reactionElment->FirstChildElement("me:activationEnergy");
				string string_Exponential_orignal = reactionAttributeValueElement->GetText();
				long double Exponentialvalue_original = atof(string_Exponential_orignal.c_str());
				string string_Exponential;
				long double Exponentvalue;


				randtemp0 = gen();
				if (attributevalue[0] == 0)
				{
					Exponentvalue = (1 - attributevalue[2] / 100 + randtemp0 * 2 * attributevalue[2] / 100)*Exponentialvalue_original;
				}
				else
				{
					Exponentvalue = Exponentialvalue_original - attributevalue[2] + randtemp0 * 2 * attributevalue[2];
				}

				ostringstream ostrExponent;
				string str_Exponent;
				ostrExponent << Exponentvalue;
				str_Exponent = ostrExponent.str();
				reactionAttributeValueElement->FirstChild()->SetValue(str_Exponent.c_str());

				indatafile << randtemp0 << "	";        //数据写入HDMR输入文件
				parametersfile << Exponentvalue << "	";   //对应的参数值
			}


		}          //end of for oneReactionAttribute

	}           //end of for reactionlist

	indatafile<<endl;
	parametersfile<<endl;
	parametersfile.close();
	indatafile.close();
	doc.SaveFile(inputfilename.c_str());
}

void CMesmer_Uncertainty_FilesDlg::OnBnClickedRun()
{
	// TODO: 在此添加控件通知处理程序代码
	int sampleSize ;
	CString samplesizestring,filePathName;
	sample_size.GetWindowTextW(samplesizestring);
	sampleSize = _ttoi(samplesizestring);
	global_samplesize = sampleSize;

	// 导出参数信息
	OnBnClickedCheckParameters();

	filepath.GetWindowTextW(filePathName);

	string xmlfilename=(char*)_bstr_t( ((wstring)(filePathName.GetBuffer())).c_str());
	string inputdatafile="HDMR_input.txt";
	static_make_mesmer_input_state.SetWindowTextW(_T("正在运行"));
	for (int filenum = 0;filenum<sampleSize; filenum++)
	{
		mt19937 eng(static_cast<unsigned long>( time(nullptr) )+filenum);
		uniform_real_distribution<double>dist(0,1);
		auto gen = bind(dist,eng);
		string filenumostring;
		ostringstream ostr;
		ostr<<filenum;
		filenumostring = ostr.str();
		string inputfilename = (string)(char*)_bstr_t( ((wstring)(mesmer_inputfile_path.GetBuffer())).c_str())+"\\mesmer_input_"+filenumostring+".xml";	
	//	AfxMessageBox((CString)inputfilename.c_str());
		alterinput(xmlfilename,inputdatafile,inputfilename,gen);
	}
	static_make_mesmer_input_state.SetWindowTextW(_T(""));
	AfxMessageBox(_T("运行结束"));
}




void CMesmer_Uncertainty_FilesDlg::OnBnClickedOutPath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_FileDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	BOOL bRet = FALSE;
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	if (pidl)
	{
		if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
		IMalloc *pMalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&pMalloc))
			&& pMalloc)
		{
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
	}
	m_FileDir = szFolder;//选择的文件夹路径
	outpathname.SetWindowTextW(m_FileDir);
	mesmer_inputfile_path = m_FileDir;

}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedMesmerOutPath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_FileDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	BOOL bRet = FALSE;
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	if (pidl)
	{
		if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
		IMalloc *pMalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&pMalloc))
			&& pMalloc)
		{
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
	}
	m_FileDir = szFolder;//选择的文件夹路径
	edit_mesmer_outfile_path.SetWindowTextW(m_FileDir);
	mesmer_outfile_path = m_FileDir;
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedGetRateConstants()
{
	// TODO: 在此添加控件通知处理程序代码
	CString samplesizestring, outfilepathstring, pnumstring;
	int samplesizevalueMin,samplesizevalueMax, pnumvalue, limiteNum;
	int temNum, preNum;
    set<double> all_T, all_P;
	set<double>::iterator itAll_T, itAll_P;
	string T_str, conc_str,p_unit;    //文件中 对应的温度，压力 <me:rateList T="1000" conc="7.33893e+018" bathGas="Ar" me:units="s-1">
	edit_outfile_samplesize.GetWindowTextW(samplesizestring);
	edit_mesmer_outfile_path.GetWindowTextW(outfilepathstring);
	samplesizevalueMax = _ttoi(samplesizestring);

	edit_outfile_sizeMin.GetWindowTextW(samplesizestring);
	samplesizevalueMin = _ttoi(samplesizestring);

	string outdatafile = "HDMR_output.txt";
	string outdatafileLn = "HDMR_output_Ln.txt";

	string outdatafileLimt = "HDMR_output_P_limit.txt";
	string outdatafileLimitLn = "HDMR_output_P_limit_Ln.txt";
	temNum = 0;
	preNum = 0;

	static_run_state.SetWindowTextW(_T("正在运行"));

	// 查看Mesmer的版本


	// 统计温度压力个数
	string filenumostringCTP;
	string filenumostring;
	ostringstream ostrCTP;
	int temTnum = 0;
	ostrCTP << (samplesizevalueMin - 1);
	filenumostringCTP = ostrCTP.str();
	string outfilenameTest = (string)(char*)_bstr_t(((wstring)(outfilepathstring.GetBuffer())).c_str()) + "\\mesmer_output_" + filenumostringCTP + ".xml";

	//AfxMessageBox((CString)outfilename.c_str());
	TiXmlDocument docTest(outfilenameTest.c_str());
	bool havefileTest = docTest.LoadFile();
	TiXmlElement *RootElementTest = docTest.RootElement();
	TiXmlElement* conditionsElements = RootElementTest->FirstChildElement("me:conditions");
	TiXmlElement* PTsElements = conditionsElements->FirstChildElement("me:PTs");
	TiXmlElement* PTpairElements = PTsElements->FirstChildElement("me:PTpair");
	
	

	if (havefileTest)
	{

		string T_str_temp, conc_str_temp;
		T_str = PTpairElements->Attribute("me:T");
		conc_str = PTpairElements->Attribute("me:P");
		p_unit = PTpairElements->Attribute("me:units");

		double p_conc = 0;
		double T_K = 0;
		T_K = atof(T_str.c_str());
		p_conc = atof(conc_str.c_str());
		all_T.insert(T_K);
		all_P.insert(p_conc);

		temNum = all_T.size();
		preNum = all_P.size();

		while (PTpairElements)
		{

			T_str_temp = PTpairElements->Attribute("me:T");
			conc_str_temp = PTpairElements->Attribute("me:P");
			// 统计温度个数
			T_K = atof(T_str_temp.c_str());
			p_conc = atof(conc_str_temp.c_str());

			all_T.insert(T_K);
			all_P.insert(p_conc);
			PTpairElements = PTpairElements->NextSiblingElement("me:PTpair");

			temNum = all_T.size();
			preNum = all_P.size();
		}

	}

	

	for (int outfilenum = (samplesizevalueMin-1); outfilenum<samplesizevalueMax; outfilenum++)
	{
		string filenumostring;
		ostringstream ostr;
		int temTnum=0;
		ostr<<outfilenum;
		filenumostring = ostr.str();
		string outfilename = (string)(char*)_bstr_t( ((wstring)(outfilepathstring.GetBuffer())).c_str())+"\\mesmer_output_"+filenumostring+".xml";
		//AfxMessageBox((CString)outfilename.c_str());
		TiXmlDocument doc(outfilename.c_str());
		bool havefile=doc.LoadFile();

		// 查看Mesmer的版本
		TiXmlElement *RootElementTest = doc.RootElement();
		TiXmlElement* metaVElements = RootElementTest->FirstChildElement("metadataList");
		TiXmlElement* mesmerVElements = metaVElements->FirstChildElement("dc:creator");
		string mesmerV = mesmerVElements->GetText();
		int mesmerVersionNum;

		if (strcmp(mesmerV.c_str(), "Mesmer v4.0") == 0)
		{
			mesmerVersionNum = 4;
		}
		else if (strcmp(mesmerV.c_str(), "Mesmer v3.0") == 0)
		{
			mesmerVersionNum = 3;
		}

		if (havefile)
		{
			
			
			TiXmlElement *RootElement = doc.RootElement();
			TiXmlElement* analysiselment = RootElement->FirstChildElement("me:analysis");
			TiXmlElement* rateListelment = analysiselment->FirstChildElement("me:rateList");

			TiXmlElement* reactionListelment = RootElement->FirstChildElement("reactionList");
			TiXmlElement* reactionElment = reactionListelment->FirstChildElement("reaction");
			TiXmlElement* rateLimteListelment;     //获取高压极限速率

			

			for (itAll_T = all_T.begin(); itAll_T != all_T.end(); itAll_T++)
			{
				reactionListelment = RootElement->FirstChildElement("reactionList");
				reactionElment = reactionListelment->FirstChildElement("reaction");
				rateLimteListelment;     //获取高压极限速率

				ostringstream ostrTmp;
				ostrTmp << *itAll_T;
				outdatafileLimt = (string)(char*)_bstr_t(((wstring)(saveRateConstantPath.GetBuffer())).c_str()) + "\\" + "HDMR_output_Plimit_T" + ostrTmp.str() + "K.txt";
				outdatafileLimitLn = (string)(char*)_bstr_t(((wstring)(saveRateConstantPath.GetBuffer())).c_str()) + "\\" + "HDMR_output_Plimit_T" + ostrTmp.str() + "K_Ln.txt";

				ofstream indatafileLimit, indatafileLimitLn;
				indatafileLimit.open(outdatafileLimt, ios::app);
				indatafileLimit.setf(ios::scientific, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
				indatafileLimit.precision(7);  // 设置精度 2

				// 速率常数取对数后输出
				indatafileLimitLn.open(outdatafileLimitLn, ios::app);
				indatafileLimitLn.setf(ios::scientific, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
				indatafileLimitLn.precision(7);  // 设置精度 2


				while (reactionElment)
				{
					
					TiXmlElement* microRateListelment;
					if (mesmerVersionNum == 3)
					{
						rateLimteListelment = reactionElment->FirstChildElement("me:microRateList");
						microRateListelment = rateLimteListelment->FirstChildElement("me:microRate");
					}
					else if (mesmerVersionNum == 4)
					{
						rateLimteListelment = reactionElment->FirstChildElement("me:canonicalRateList");
						microRateListelment = rateLimteListelment->FirstChildElement("me:kinf");
					}
					
					limiteNum = 0;
					while (microRateListelment)         //统计每个反应中共计算了多少个温度，倒数第二个就是
					{
						
						//提取高压极限
						int limiteIndex;
						string limitRateConstant, limitT;
						TiXmlElement* limitRateElement;
						TiXmlElement* temlimitRateElement;

						temlimitRateElement = microRateListelment->FirstChildElement("me:T");
						limitT = temlimitRateElement->GetText();
						double limitTnum = atof(limitT.c_str());
		//				microRateListelment = rateLimteListelment->FirstChildElement("me:microRate");
	//					limiteIndex = limiteNum - 2;     //倒数第二个才是对应温度的高压极限
					/*	ostringstream ostrTmp;
						ostrTmp << *itAll_T;*/
						if ( *itAll_T == limitTnum )
						{
							ofstream test ;
							test.open("test.txt", ios::app);
							test << *itAll_T << endl << ostrTmp.str() << endl;
							test.close();

							limitRateElement = microRateListelment->FirstChildElement("me:val");
							limitRateConstant = limitRateElement->GetText();
							long double limitRateconstantValueLn = atof(limitRateConstant.c_str());
							limitRateconstantValueLn = log(limitRateconstantValueLn);

							indatafileLimit << limitRateConstant << "	";
							indatafileLimitLn << limitRateconstantValueLn << "	";

							//break;
						}
						
						if (mesmerVersionNum == 3)
						{
							microRateListelment = microRateListelment->NextSiblingElement("me:microRate");
						}
						else if (mesmerVersionNum == 4)
						{
							microRateListelment = microRateListelment->NextSiblingElement("me:kinf");
						}
						


					}
			//		rateLimteListelment = rateLimteListelment->NextSiblingElement("me:microRateList");
					reactionElment = reactionElment->NextSiblingElement("reaction");

				}
				indatafileLimit << endl;
				indatafileLimitLn << endl;
				indatafileLimit.close();
				indatafileLimitLn.close();
			}
			
			
	//		ofstream test1;
	//		test1.open("test1.txt", ios::app);
	//		test1 << temNum;
	//		test1.close();

			TiXmlElement* rateListelmenttemp = rateListelment;
			
			// itAll_T, itAll_P;
			//set<double>::iterator indexT;
//			for (itAll_T = all_T.begin(); itAll_T != all_T.end(); itAll_T++)
			for (itAll_P = all_P.begin(); itAll_P != all_P.end(); itAll_P++)
			{
			//	temTnum++;
			//	if (temTnum == 9)
			//	{
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//		rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
			//	}
//				for (itAll_P = all_P.begin(); itAll_P != all_P.end(); itAll_P++)
				for (itAll_T = all_T.begin(); itAll_T != all_T.end(); itAll_T++)
				{
					
					ostringstream ostrTmp,ostrPre;
					
						
					ostrTmp << *itAll_T;
					ostrPre << *itAll_P;
					filenumostring = ostrPre.str() + p_unit +"_T" + ostrTmp.str() + "K";
					outdatafile = (string) (char*) _bstr_t(((wstring) (saveRateConstantPath.GetBuffer())).c_str()) + "\\" + "HDMR_output_P" + filenumostring + ".txt";
					outdatafileLn = (string) (char*) _bstr_t(((wstring) (saveRateConstantPath.GetBuffer())).c_str()) + "\\" + "HDMR_output_P" + filenumostring + "_Ln.txt";
					
					TiXmlElement* RateConstantelment = rateListelmenttemp->FirstChildElement("me:firstOrderRate");
					string rateconstant;

					ofstream indatafile, indatafileLn;
					indatafile.open(outdatafile, ios::app);
					indatafile.setf(ios::scientific, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
					indatafile.precision(7);  // 设置精度 2

					// 速率常数取对数后输出
					indatafileLn.open(outdatafileLn, ios::app);
					indatafileLn.setf(ios::scientific, ios::floatfield);  // 设定为 fixed 模式，以小数点表示浮点数
					indatafileLn.precision(7);  // 设置精度 2

					while (RateConstantelment)
					{
						rateconstant = RateConstantelment->GetText();
						long double rateconstantValueLn = atof(rateconstant.c_str());
						rateconstantValueLn = log(rateconstantValueLn);
						indatafile << rateconstant << "	";
						indatafileLn << rateconstantValueLn << "	";
						RateConstantelment = RateConstantelment->NextSiblingElement("me:firstOrderRate");
					}

					indatafile << endl;
					indatafile.close();

					indatafileLn << endl;
					indatafileLn.close();

					rateListelmenttemp = rateListelmenttemp->NextSiblingElement("me:rateList");
				}
			}


		}
		else
		{
			AfxMessageBox(_T(" Data loss ,please reexamine the files carefully"));
			return;
		}
		

	}
	static_run_state.SetWindowTextW(_T(""));
	AfxMessageBox(_T("运行结束"));
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedRunRateConstant()
{
	// TODO: 在此添加控件通知处理程序代码
	static_run_state.SetWindowTextW(_T("正在运行"));

	int sampleSize ;
	CString samplesizestring,outfilepath;

	


	edit_outfile_samplesize.GetWindowTextW(samplesizestring);
	sampleSize = _ttoi(samplesizestring);
	edit_mesmer_outfile_path.GetWindowTextW(outfilepath);
	for (int filenum = 0;filenum<sampleSize; filenum++)
	{
		string command;
		string filenumostring;
		ostringstream ostr;
		ostr<<filenum;
		filenumostring = ostr.str();
		string inputfilename = (string)(char*)_bstr_t( ((wstring)(mesmer_inputfile_path.GetBuffer())).c_str())+"\\mesmer_input_"+filenumostring+".xml";
		string outputfilename = (string)(char*)_bstr_t( ((wstring)(outfilepath.GetBuffer())).c_str())+"\\mesmer_output_"+filenumostring+".xml";
		command = "mesmer "+inputfilename+" -o " + outputfilename;;

		system(command.c_str());

	}


	static_run_state.SetWindowTextW(_T(""));
}






void CAboutDlg::OnHelpCopyright2014shuangli()
{
	// TODO:  在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://flame.nsrl.ustc.edu.cn/home"), NULL, NULL, SW_SHOWNORMAL);
}


void CMesmer_Uncertainty_FilesDlg::OnHelpSli()
{
	// TODO:  在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://flame.nsrl.ustc.edu.cn/people/?sid=13"), NULL, NULL, SW_SHOWNORMAL);
}


void CMesmer_Uncertainty_FilesDlg::OnHelpCopyright2014shuangli()
{
	// TODO:  在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://flame.nsrl.ustc.edu.cn/home"), NULL, NULL, SW_SHOWNORMAL);
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedButton1Modified()
{
	// TODO:  在此添加控件通知处理程序代码
	int sampleSize,newGrainSize;
	CString samplesizestring, filePathName, modifiedGrainSizeString, TP_FilePathNameString;
	double temp;
	vector<double> vectorT;
	vector<double> vectorP;

	sample_size.GetWindowTextW(samplesizestring);
	sampleSize = _ttoi(samplesizestring);
	outpathname.GetWindowTextW(filePathName);
	
	modifiedGrainSize.GetWindowTextW(modifiedGrainSizeString);
	//newGrainSize = _ttoi(modifiedGrainSizeString);

	// 提取温度压力
	//TP_FileName
	TP_FileName.GetWindowTextW(TP_FilePathNameString);
	string TP_FilePathName = (string)(char*)_bstr_t(((wstring)(TP_FilePathNameString.GetBuffer())).c_str());
	//ifstream TPinputfile("TP.txt", std::ios::in);
	ifstream TPinputfile(TP_FilePathName, std::ios::in);
	
	if (!modifyGrainSize.GetCheck())
	{
		AfxMessageBox(_T("Warning: grainsize not be modified!"));
	}
	else
	{
		for (int inputfileIndex = 0; inputfileIndex < sampleSize; inputfileIndex++)
		{
			string filenumostring;
			ostringstream ostr;
			int conditionsize;
			int temTnum = 0;
			ostr << inputfileIndex;
			filenumostring = ostr.str();
			string inputfilename = (string) (char*) _bstr_t(((wstring) (mesmer_inputfile_path.GetBuffer())).c_str()) + "\\mesmer_input_" + filenumostring + ".xml";
			//string inputfilename = "mesmer_input_" + filenumostring + ".xml";
			//AfxMessageBox((CString)outfilename.c_str());
			TiXmlDocument doc(inputfilename.c_str());
			bool havefile = doc.LoadFile();
			if (havefile)
			{

				TiXmlElement *RootElement = doc.RootElement();
				TiXmlElement* modelParametersElment = RootElement->FirstChildElement("me:modelParameters");
				TiXmlElement* grainSizeElment = modelParametersElment->FirstChildElement("me:grainSize");
				grainSizeElment->FirstChild()->SetValue((char*) _bstr_t(((wstring) (modifiedGrainSizeString.GetBuffer())).c_str()));

				doc.SaveFile(inputfilename.c_str());
			}
			else
			{
				AfxMessageBox((CString) ("Cannot find " + inputfilename).c_str());
			}
		}
	}

	if (!isModifyCondition.GetCheck())
	{
		AfxMessageBox(_T("Run over"));
	}
	else
	{
		if (!TPinputfile)
		{
			AfxMessageBox(_T("Cannot find TP.txt"));
		}
		else
		{

			while (TPinputfile >> temp)
			{
				vectorT.push_back(temp);
				TPinputfile >> temp;
				vectorP.push_back(temp);
			}

			TPinputfile.close();

			for (int inputfileIndex = 0; inputfileIndex < sampleSize; inputfileIndex++)
			{
				string filenumostring;
				ostringstream ostr;
				int conditionsize;
				int temTnum = 0;
				ostr << inputfileIndex;
				filenumostring = ostr.str();
				string inputfilename = (string) (char*) _bstr_t(((wstring) (mesmer_inputfile_path.GetBuffer())).c_str()) + "\\mesmer_input_" + filenumostring + ".xml";
				//AfxMessageBox((CString)outfilename.c_str());
				TiXmlDocument doc(inputfilename.c_str());
				bool havefile = doc.LoadFile();
				if (havefile)
				{
					TiXmlElement *RootElement = doc.RootElement();

					// 修改温度压力
					TiXmlElement*conditionElment = RootElement->FirstChildElement("me:conditions");
					TiXmlElement* PTsElment = conditionElment->FirstChildElement("me:PTs");
					PTsElment->Clear();
					conditionsize = vectorT.size();

					for (int conditionIndex = 0; conditionIndex < conditionsize; conditionIndex++)
					{

						TiXmlElement * newTPNode = new TiXmlElement("me:PTpair");
						newTPNode->SetAttribute("me:units", "atm");
						newTPNode->SetDoubleAttribute("me:P", vectorP[conditionIndex]);
						newTPNode->SetAttribute("me:T", vectorT[conditionIndex]);
						newTPNode->SetAttribute("me:precision", "d");
						PTsElment->LinkEndChild(newTPNode);
					}

					doc.SaveFile(inputfilename.c_str());
				}
				else
				{
					AfxMessageBox((CString) ("Cannot find " + inputfilename).c_str());
				}
			}


			AfxMessageBox(_T("Run over"));

		}
	}


	
}



void CMesmer_Uncertainty_FilesDlg::OnBnClickedButtonLoadConfig()
{
	// TODO:  在此添加控件通知处理程序代码
	// 打开文件
	string moleculeName,attributeName,attributeValueStr;
	double attributeValue;
	CString FilePathName;
	vector<string> allMoleculeName;
	vector<string> allAttributeName;
	vector<double> allAttributeValue;
	vector<double> allAttributeValueFlag;
	set<string> allDifferentMoleculeName;
	set<string>::iterator allDifferentMoleculeName_iter;
	set<string> allDifferentAttributeName;
	set<string>::iterator allDifferentAttributeName_iter;
	set<string> oneMoleculeDifferentAttributeName;
	set<string>::iterator oneDifferentAttributeName_iter;
	vector<int> positionOneMolecule;
	vector<int> positionOneMoleculeOneAttributeName;
	vector<double> oneMoleculeOneAttributeValue;
	map<string,vector<double>> temp_attribute_value;


	POSITION pos;
	CFileDialog mFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("Txt Files (*.dat) | *.dat|Txt Files (*.txt) | *.txt|"), AfxGetMainWnd());
	pos = mFileDlg.GetStartPosition();

	CString cstemp;
	if (mFileDlg.DoModal() == IDOK)
	{
		FilePathName = mFileDlg.GetNextPathName(pos);
	}
	ifstream file(FilePathName);
	string inputstring;
	stringstream ss;
	ss << file.rdbuf();
	file.close();
	inputstring = ss.str();

	mollecule_attribute_uncertainty_value.clear();

	std::regex_constants::syntax_option_type fl = std::regex_constants::icase;
	const std::tr1::regex pattern("^\\d+\\s+(\\w+)\\s+(\\w+)\\s+±(\\d+\\.?\\d*)%\\s*\\n", fl);
	const std::tr1::regex pattern1("^\\d+\\s+(\\w+)\\s+(\\w+)\\s+±(\\d+\\.?\\d*)\\s*\\n", fl);
	std::tr1::smatch result;
	std::string::const_iterator itS = inputstring.begin();
	std::string::const_iterator itE = inputstring.end();

//	ofstream TPinputfile("TestLoadConfig.txt", std::ios::out);

	while (regex_search(itS, itE, result, pattern))
	{
		moleculeName = string(result[1].first, result[1].second);
	    attributeName = string(result[2].first, result[2].second);
		attributeValue = atof(string(result[3].first, result[3].second).c_str());
		allMoleculeName.push_back(moleculeName);
		allAttributeName.push_back(attributeName);
		allAttributeValue.push_back(attributeValue);
		allAttributeValueFlag.push_back(0);

		allDifferentMoleculeName.insert(moleculeName);
		allDifferentAttributeName.insert(attributeName);

		itS = result[0].second;
	}

	itS = inputstring.begin();
	itE = inputstring.end();
	while (regex_search(itS, itE, result, pattern1))
	{
		moleculeName = string(result[1].first, result[1].second);
		attributeName = string(result[2].first, result[2].second);
		attributeValue = atof(string(result[3].first, result[3].second).c_str());
		allMoleculeName.push_back(moleculeName);
		allAttributeName.push_back(attributeName);
		allAttributeValue.push_back(attributeValue);
		allAttributeValueFlag.push_back(1);

		allDifferentMoleculeName.insert(moleculeName);
		allDifferentAttributeName.insert(attributeName);

		itS = result[0].second;
	}

	string moleculeNameTemp;
	string attributeNameTemp;
	for (auto iter = allDifferentMoleculeName.begin(); iter != allDifferentMoleculeName.end(); iter++)
	{
		moleculeNameTemp = *iter;
		temp_attribute_value.erase(temp_attribute_value.begin(), temp_attribute_value.end());
		positionOneMolecule.clear();
		oneMoleculeDifferentAttributeName.erase(oneMoleculeDifferentAttributeName.begin(), oneMoleculeDifferentAttributeName.end());
		for (int i = 0; i < allMoleculeName.size();i++)
		{
			if (allMoleculeName[i]== moleculeNameTemp)
			{
				oneMoleculeDifferentAttributeName.insert(allAttributeName[i]);
				positionOneMolecule.push_back(i);
			}
		}


		for (auto iterAttribute = oneMoleculeDifferentAttributeName.begin(); iterAttribute != oneMoleculeDifferentAttributeName.end(); iterAttribute++)
		{
			attributeNameTemp = *iterAttribute;
			positionOneMoleculeOneAttributeName.clear();

			for (int j = 0; j < positionOneMolecule.size();j++)
			{
				if (allAttributeName[positionOneMolecule[j]] == attributeNameTemp)
				{
					positionOneMoleculeOneAttributeName.push_back(positionOneMolecule[j]);
				}
			}	

			oneMoleculeOneAttributeValue.clear();

			oneMoleculeOneAttributeValue.push_back(allAttributeValueFlag[positionOneMoleculeOneAttributeName[0]]);
			oneMoleculeOneAttributeValue.push_back(positionOneMoleculeOneAttributeName.size());

			for (int t = 0; t < positionOneMoleculeOneAttributeName.size();t++)
			{
				oneMoleculeOneAttributeValue.push_back(allAttributeValue[positionOneMoleculeOneAttributeName[t]]);
			}

			temp_attribute_value.insert(make_pair(attributeNameTemp, oneMoleculeOneAttributeValue));
			
		}
		mollecule_attribute_uncertainty_value.insert(make_pair(moleculeNameTemp, temp_attribute_value));
	}

	OnBnClickedCheckParameters();

//	TPinputfile.close();
}


void CMesmer_Uncertainty_FilesDlg::OnBnClickedButtonSaveRatePath()
{
	// TODO:  在此添加控件通知处理程序代码
	CString m_FileDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	BOOL bRet = FALSE;
	TCHAR szFolder[MAX_PATH * 2];
	szFolder[0] = _T('\0');
	if (pidl)
	{
		if (SHGetPathFromIDList(pidl, szFolder))
			bRet = TRUE;
		IMalloc *pMalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&pMalloc))
			&& pMalloc)
		{
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
	}
	saveRateConstantPath = szFolder;//选择的文件夹路径
	editSavePath.SetWindowTextW(saveRateConstantPath);
}
