
// Mesmer_Uncertainty_FilesDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<vector>
#include<set>
#include <map>
using namespace std;
// CMesmer_Uncertainty_FilesDlg 对话框
class CMesmer_Uncertainty_FilesDlg : public CDialogEx
{
// 构造
public:
	CMesmer_Uncertainty_FilesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MESMER_UNCERTAINTY_FILES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	vector<CString> allmolecule;
	vector<CString> allreaction;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	double NA = 6.022e23;
	double R = 8.314;

public:
	afx_msg void OnBnClickedOpenFile();
	CStatic filepath;
	CString string_filepathname;
	CComboBox combo_moleculelist;
	
	CComboBox energy_unit;
	CComboBox vib_unit;
	CComboBox rot_unit;
	CComboBox image_unit;
	CComboBox delta_EDown;
	CComboBox sigma_unit;
	CComboBox epsilon_unit;
	CComboBox deltaEDownTE_unit;
	CComboBox hinderedRotor_unit;
	CEdit edit_energy;
	CEdit edit_vib_num;
	CEdit edit_vib;
	CEdit edit_rot_num;
	CEdit edit_rot;
	CEdit edit_image;
	CEdit edit_deltaEDown;
	CEdit edit_sigma;
	CEdit edit_epsilon;
	CEdit edit_deltaEDownTE;
	CEdit edit_hinderedRotor;
	afx_msg void OnBnClickedEnergySelect();
	CButton select_energy;
	CButton select_vib;
	CButton select_rot;
	CButton select_image;
	CButton select_deltaEDown;
	CButton select_sigma;
	CButton select_epsilon;
	CButton select_deltaEDownTE;
	CButton select_hinderedRotor;
	map<string,map<string,bool>> mollecule_attribute_uncertainty_flag;
	map<string,map<string,vector<double>>> mollecule_attribute_uncertainty_value;
	map<string, map<string, bool>> reaction_attribute_uncertainty_flag;
	map<string, map<string, vector<double>>> reaction_attribute_uncertainty_value;

	CString mesmer_inputfile_path;
	CString mesmer_outfile_path;
	CString saveRateConstantPath;
	int global_samplesize;

	template<class T>
	void alterinput(string ,string ,string ,T ) ;

	int parameter_num;
	afx_msg void OnBnClickedVibSelect();
	afx_msg void OnBnClickedRotSelect();
	afx_msg void OnBnClickedImageSelect();
	afx_msg void OnBnClickedDeltaEDownSelect();
	afx_msg void OnBnClickedSigmaSelect();
	afx_msg void OnBnClickedEpsilonSelect();
	afx_msg void OnBnClickedAddOneRecord();
	afx_msg void OnBnClickedCheckParameters();
	afx_msg void OnBnClickedRun();
	CEdit sample_size;
	afx_msg void OnBnClickedOutPath();
	CStatic outpathname;
	CStatic editSavePath;
	CEdit edit_p_num;
	afx_msg void OnBnClickedMesmerOutPath();
	CEdit edit_mesmer_outfile_path;
	afx_msg void OnBnClickedGetRateConstants();
	CEdit edit_outfile_samplesize;
	CStatic static_run_state;
	afx_msg void OnBnClickedRunRateConstant();
	CStatic static_make_mesmer_input_state;
	
	
	
	afx_msg void OnBnClickedDeltaTESelect();
	afx_msg void OnBnClickedHinderedRotorSelect();
	CComboBox combo_reactionlist;
	CButton select_preExponential;
	CEdit edit_preExponential;
	CComboBox preExponential_unit;
	afx_msg void OnBnClickedpreExponentialSelect();
	afx_msg void OnBnClickedAddOneReactionRecord();
	CButton select_Exponent;
	CEdit edit_Exponent;
	CComboBox Exponent_unit;
	afx_msg void OnBnClickedExponentSelect();
	CMenu * pMenu;
	afx_msg void OnHelpSli();
//	afx_msg void OnHelpCopyright2014shuangli();
	afx_msg void OnHelpCopyright2014shuangli();
	CEdit edit_outfile_sizeMin;
	CEdit modifiedGrainSize;
	CButton ModifiedSettings;
	afx_msg void OnBnClickedButton1Modified();
	afx_msg void OnBnClickedCheck12();
	CButton isModifyCondition;
	CButton LoadConfig;
	afx_msg void OnBnClickedButtonLoadConfig();
	CButton buttonSaveRatePath;
	afx_msg void OnBnClickedButtonSaveRatePath();
	CButton modifyGrainSize;
	CEdit TP_FileName;
};
