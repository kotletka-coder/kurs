#include <QWidget>
#include <QVector>
#include <QString>
class QListWidget;
class QLineEdit;
struct OrderItem
{    
	int orderId;
	QString product;};
struct ClientItem
{   
	int clientId;  
	QString name; 
	QVector<OrderItem> orders;
};
class MainWindow : public QWidget
{    
Q_OBJECT
	public:  
	MainWindow();
	private slots:   
		void onAddClient();  
	void onAddOrder();  
	void onDeleteOrder(); 
	void onDeleteClient();
	private: 
	QWidget* createAddClientWidget(); 
	QWidget* createAddOrderWidget();   
	QWidget* createDeleteOrderWidget(); 
	QWidget* createDeleteClientWidget();  
	void refreshList();  
	int m_nextClientId;  
	QVector<ClientItem> m_clients; 
	QListWidget* m_clientsList;   
	QLineEdit* m_clientNameEdit; 
	QLineEdit* m_orderClientIdEdit; 
	QLineEdit* m_productEdit; 
	QLineEdit* m_orderIdEdit;   
	QLineEdit* m_delOrderIdEdit; 
	QLineEdit* m_delClientIdEdit;
};

