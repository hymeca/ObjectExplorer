#pragma once

#include "VirtualListView.h"
#include "Interfaces.h"

class CObjectManagerView : 
	public CWindowImpl<CObjectManagerView>,
	public CVirtualListView<CObjectManagerView> {
public:
	DECLARE_WND_CLASS(nullptr)

	CObjectManagerView(IMainFrame* frame);

	CString GetDirectoryPath() const;
	void OnFinalMessage(HWND) override;
	void DoSort(const SortInfo* si);
	bool IsSortable(int column) const;

	BEGIN_MSG_MAP(CObjectManagerView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnTreeSelectionChanged)
		NOTIFY_CODE_HANDLER(LVN_GETDISPINFO, OnListGetDispInfo)
		COMMAND_ID_HANDLER(ID_VIEW_REFRESH, OnRefresh)
		CHAIN_MSG_MAP(CVirtualListView<CObjectManagerView>)
	END_MSG_MAP()

private:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTreeSelectionChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT OnListGetDispInfo(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT OnRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void InitTree();
	void UpdateList(bool newNode);
	void EnumDirectory(CTreeItem root, const CString& path);

	struct ObjectData {
		CString Name, FullName, Type;
	};
	static bool CompareItems(const ObjectData& data1, const ObjectData& data2, int col, bool asc);

private:
	CTreeViewCtrlEx m_Tree;
	CListViewCtrl m_List;
	std::vector<ObjectData> m_Objects;
	CSplitterWindow m_Splitter;
	IMainFrame* m_pFrame;
};

