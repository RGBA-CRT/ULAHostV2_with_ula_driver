void META_CLASS::GBASwitch()
{
	MessageBox("Turn off GBA !!" ,"Project xLA", MB_ICONEXCLAMATION);

	// Turn On your GBA
	if(m_pULATurnOnDlg == NULL){
		m_pULATurnOnDlg = new CULATurnOnDlg;
		m_pULATurnOnDlg->Create(this);
	}
	else{
		m_pULATurnOnDlg->BringWindowToTop();
	}
}

void META_CLASS::EndULATurnOnDlg()
{
	m_pULATurnOnDlg = NULL;

}
