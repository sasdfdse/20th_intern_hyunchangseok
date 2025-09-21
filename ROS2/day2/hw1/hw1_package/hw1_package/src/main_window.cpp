#include "../include/hw1_package/main_window.hpp"
#include "rclcpp/rclcpp.hpp"

MainWindow::MainWindow(std::shared_ptr<QNode> qnode, QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindowDesign)
  , qnode_(qnode)
{
  ui->setupUi(this);
  log = ui->log;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    static QVector<QString> queue_v;   // static이면 클릭할 때마다 누적 가능
    queue_v.prepend(ui->lineEdit->text());




    if (!queue_v.isEmpty()) {
        QString first_qstr = queue_v[0];


        std::string tostring = first_qstr.toStdString();


        std_msgs::msg::String msg;
        msg.data = tostring;

        qnode_->publisher_->publish(msg);

        ui->lineEdit->clear();
        ui->log->append(QString("[Publish] ") + QString::fromStdString(tostring));

    }

}
