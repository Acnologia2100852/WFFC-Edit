// SelectDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "SelectDialogue.h"
#include "ObjectController.h"

// SelectDialogue dialog

IMPLEMENT_DYNAMIC(SelectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(SelectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &SelectDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &SelectDialogue::OnBnClickedOk)		
	ON_LBN_SELCHANGE(IDC_LIST1, &SelectDialogue::Select)	//listbox
END_MESSAGE_MAP()


SelectDialogue::SelectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_sceneGraph = SceneGraph;
}

SelectDialogue::SelectDialogue(CWnd * pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

SelectDialogue::~SelectDialogue()
{
}

///pass through pointers to the data in the tool we want to manipulate
void SelectDialogue::SetObjectData(std::vector<SceneObject>* SceneGraph)
{
	m_sceneGraph = SceneGraph;
	

	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = ObjectController::Instance().GetDisplayObjects()->size();
	for (int i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.

		int id = ((*ObjectController::Instance().GetDisplayObjects())[i].m_ID);
		std::wstring listBoxEntry = std::to_wstring(id);
		m_listBox.AddString(listBoxEntry.c_str());
	}
}


void SelectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

void SelectDialogue::End()
{
	ObjectController::Instance().isEditing = false;
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void SelectDialogue::Select()
{
	int index = m_listBox.GetCurSel();
	CString currentSelectionValue;
	
	m_listBox.GetText(index, currentSelectionValue);

	m_currentSelection = _ttoi(currentSelectionValue);

	if(std::find(ObjectController::Instance().selectedObjs.begin(), ObjectController::Instance().selectedObjs.end(), m_currentSelection) != ObjectController::Instance().selectedObjs.end())
	{
		bool isDuplicate = false;

		if (!ObjectController::Instance().selectedObjs.empty()) 
		{
			isDuplicate = RemoveIntFromVector(ObjectController::Instance().selectedObjs, m_currentSelection);
		}

		if(m_currentSelection != -1 && !isDuplicate)
		{
			ObjectController::Instance().selectedObjs.push_back(m_currentSelection);

			return;
		}

		if (m_currentSelection != -1 && isDuplicate) 
		{
			ObjectController::Instance().RemoveTexture(m_currentSelection);
		}
	}

}

BOOL SelectDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//uncomment for modal only
/*	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void SelectDialogue::PostNcDestroy()
{
	ObjectController::Instance().isEditing = false;
}




// SelectDialogue message handlers callback   - We only need this if the dailogue is being setup-with createDialogue().  We are doing
//it manually so its better to use the messagemap
/*INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		//	EndDialog(hwndDlg, wParam);
			DestroyWindow(hwndDlg);
			return TRUE;
			

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			break;
		}
	}
	
	return INT_PTR();
}*/


void SelectDialogue::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

