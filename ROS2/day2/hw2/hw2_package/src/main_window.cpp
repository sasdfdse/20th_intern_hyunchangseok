#include "hw2_package/main_window.hpp"
#include "rclcpp/rclcpp.hpp"
#include <thread>

#include <QKeyEvent>
MainWindow::MainWindow(std::shared_ptr<QNode> qnode, QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindowDesign)
  , qnode_(qnode)
{ ui->setupUi(this);
  log_text = ui->log_text;
  
  QObject::connect(qnode_.get(), &QNode::log, this, &MainWindow::updateLog);
  
  ui->centralwidget->setFocus();
  ui->centralwidget->setFocusPolicy(Qt::StrongFocus);

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   qnode_->drawSquare();
}

void MainWindow::on_pushButton_2_clicked()
{
    qnode_->drawtriangle();
}

void MainWindow::on_pushButton_3_clicked()
{
    qnode_->drawcircle();
}

void MainWindow::updateLog(const QString& message)
{
  ui->log_text->append(message);
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        qnode_->move_forward();
        break;
    case Qt::Key_S:
        qnode_->move_back();
        break;
    case Qt::Key_A:
        qnode_->turn_left();
        break;
    case Qt::Key_D:
        qnode_->turn_right();
        break;
    default:
        break;
    }
    QWidget::keyPressEvent(event);
}
