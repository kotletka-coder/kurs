#include "mainwindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
MainWindow::MainWindow()    
	: m_nextClientId(1),   
	m_clientsList(new QListWidget(this)),   
	m_clientNameEdit(new QLineEdit(this)),   
	m_orderClientIdEdit(new QLineEdit(this)),  
	m_productEdit(new QLineEdit(this)),   
	m_orderIdEdit(new QLineEdit(this)),    
	m_delOrderIdEdit(new QLineEdit(this)),
	m_delClientIdEdit(new QLineEdit(this))
{ 
	m_clientsList->setMinimumWidth(300);  
	
	QVBoxLayout* rightLay = new QVBoxLayout();  
	rightLay->addWidget(createAddClientWidget()); 
	rightLay->addWidget(createAddOrderWidget());  
	rightLay->addWidget(createDeleteOrderWidget()); 
	rightLay->addWidget(createDeleteClientWidget()); 
	
	QHBoxLayout* mainLay = new QHBoxLayout(this);  
	mainLay->addWidget(m_clientsList); 
	mainLay->addLayout(rightLay); 
	
	setLayout(mainLay);  
	show();
}
QWidget* MainWindow::createAddClientWidget()
{  
	QGroupBox* box = new QGroupBox("Добавить клиента", this);  
	QVBoxLayout* lay = new QVBoxLayout(box); 
	QFormLayout* form = new QFormLayout();  

	form->addRow("Имя:", m_clientNameEdit);  

	QPushButton* btn = new QPushButton("Добавить", box);

	lay->addLayout(form);  
	lay->addWidget(btn); 

	connect(btn, &QPushButton::clicked, this, &MainWindow::onAddClient); 
	return box;
}
QWidget* MainWindow::createAddOrderWidget()
{   
	QGroupBox* box = new QGroupBox("Добавить заказ клиента", this);  
	QVBoxLayout* lay = new QVBoxLayout(box);
	QFormLayout* form = new QFormLayout(); 

	form->addRow("ID клиента:", m_orderClientIdEdit);   
	form->addRow("Товар:", m_productEdit); 
	form->addRow("ID заказа:", m_orderIdEdit);  

	QPushButton* btn = new QPushButton("Добавить заказ", box);

	lay->addLayout(form);  
	lay->addWidget(btn);  

	connect(btn, &QPushButton::clicked, this, &MainWindow::onAddOrder);
	return box;
}
QWidget* MainWindow::createDeleteOrderWidget()
{
	QGroupBox* box = new QGroupBox("Удалить заказ", this); 
	QVBoxLayout* lay = new QVBoxLayout(box); 
	QFormLayout* form = new QFormLayout(); 

	form->addRow("id заказа:", m_delOrderIdEdit); 

	QPushButton* btn = new QPushButton("Удалить заказ", box);  

	lay->addLayout(form);  
	lay->addWidget(btn);  

	connect(btn, &QPushButton::clicked, this, &MainWindow::onDeleteOrder);
	return box;
}
QWidget* MainWindow::createDeleteClientWidget()
{ 
	QGroupBox* box = new QGroupBox("Удалить клиента", this); 
	QVBoxLayout* lay = new QVBoxLayout(box); 
	QFormLayout* form = new QFormLayout(); 

	form->addRow("id клиента:", m_delClientIdEdit);  

	QPushButton* btn = new QPushButton("Удалить клиента", box);  

	lay->addLayout(form); 
	lay->addWidget(btn);  

	connect(btn, &QPushButton::clicked, this, &MainWindow::onDeleteClient);
	return box;
}
void MainWindow::onAddClient()
{  
	QString name = m_clientNameEdit->text().trimmed(); 
	if (name.isEmpty()) {    
		return;  
	}  

	ClientItem c;  
	c.clientId = m_nextClientId++; 
	c.name = name; 

	m_clients.append(c);  
	m_clientNameEdit->clear(); 
	refreshList();
}
void MainWindow::onAddOrder()
{  
	bool okClient = false; 
	bool okOrder = false;  
	int clientId = m_orderClientIdEdit->text().toInt(&okClient); 
	int orderId = m_orderIdEdit->text().toInt(&okOrder);

	QString product = m_productEdit->text().trimmed();  

	if (!okClient || !okOrder || product.isEmpty()) {    
		return; 
	} 
	for (ClientItem& c : m_clients) {   
		if (c.clientId == clientId) {  
			c.orders.append({orderId, product});    
			m_orderClientIdEdit->clear();    
			m_productEdit->clear();        
			m_orderIdEdit->clear();      
			refreshList();       
			return;      
		}  
	}
}
void MainWindow::onDeleteOrder()
{ 
	bool ok = false;   
	int orderId = m_delOrderIdEdit->text().toInt(&ok);  
	if (!ok) {  
		return;   
	}   

	for (ClientItem& c : m_clients) {    
		for (int i = 0; i < c.orders.size(); ++i) {
			if (c.orders[i].orderId == orderId) { 
				c.orders.removeAt(i);  
				m_delOrderIdEdit->clear();  
				refreshList();       
				return;       
			}    
		}
	}
}
void MainWindow::onDeleteClient()
{
	bool ok = false;  
	int clientId = m_delClientIdEdit->text().toInt(&ok); 
	if (!ok)
	{  
		return;
	} 
	for (int i = 0; i < m_clients.size(); ++i) {  
		if (m_clients[i].clientId == clientId) {  
			m_clients.removeAt(i);        
			m_delClientIdEdit->clear();  
			refreshList();        
			return;     
		}  
	}
}
void MainWindow::refreshList()
{
	m_clientsList->clear(); 
	for (const ClientItem& c : m_clients) {  
		m_clientsList->addItem(QString("Клиент #%1: %2").arg(c.clientId).arg(c.name));    
		for (const OrderItem& o : c.orders) {       
			m_clientsList->addItem(QString("    Заказ #%1 — %2").arg(o.orderId).arg(o.product)); 
		}
	}
}

