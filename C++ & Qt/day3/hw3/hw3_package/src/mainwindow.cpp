#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>


MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // UI 초기화
    gridLayout = new QGridLayout(ui->gridFrame);
    gridLayout->setSpacing(2);
    ui->gridFrame->setLayout(gridLayout);

    gridLayout2 = new QGridLayout(ui->gridFrame2);
    gridLayout2->setSpacing(2);
    ui->gridFrame2->setLayout(gridLayout2);

}


void MyWidget::on_pushButton_clicked()
{
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // 버튼 삭제
        delete child;
    }
    while ((child = gridLayout2->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (int r = 0; r < Row; r++) {
        for (int c = 0; c < Col; c++) {
            QPushButton *cell = new QPushButton(QString("(%1,%2)").arg(r).arg(c));
            cell->setFixedSize(40, 40);
            gridLayout->addWidget(cell, r, c);

            connect(cell, &QPushButton::clicked, this, [=]() {
                if (startRow == -1 && startCol == -1) {   // 시작점 선택
                    startRow = r;
                    startCol = c;
                    cell->setStyleSheet("background-color: green;");
                }
                else if (endRow == -1 && endCol == -1) {  // 끝점 선택
                    endRow = r;
                    endCol = c;
                    cell->setStyleSheet("background-color: red;");
                }

                qDebug() << "시작: (" << startRow << "," << startCol << ")"
                         << "끝: (" << endRow << "," << endCol << ")";
            });

        }
    }
    for (int r = 0; r < Row; r++) {
        for (int c = 0; c < Col; c++) {
            QPushButton *cell = new QPushButton(QString("(%1,%2)").arg(r).arg(c));
            cell->setFixedSize(40, 40);
            gridLayout2->addWidget(cell, r, c);
            connect(cell, &QPushButton::clicked, this, [=]() {
                if (startRow1== -1 && startCol1 == -1) {
                    startRow1 = r;
                    startCol1= c;
                    cell->setStyleSheet("background-color: green;");
                }
                else if (endRow1 == -1 && endCol1 == -1) {
                    endRow1 = r;
                    endCol1 = c;
                    cell->setStyleSheet("background-color: red;");
                }

                qDebug() << "시작: (" << startRow1 << "," << startCol1 << ")"
                         << "끝: (" << endRow1 << "," << endCol1 << ")";
            });

        }
    }

}


void MyWidget::on_spinBox_valueChanged(int arg)
{

    Col = arg;
}

void MyWidget::on_spinBox_2_valueChanged(int arg1)
{
    Row = arg1;
}


void MyWidget::on_pushButton_2_clicked(bool checked)
{
    AStar_algorithm();
    Dijkstra_algorithm();
}

struct Node {
    int row, col;
    int g, h, f;
    Node* parent;
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

void MyWidget::AStar_algorithm() {
    if (startRow == -1 || endRow == -1) {
        qDebug() << "시작점/끝점이 지정되지 않았습니다.";
        return;
    }

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    std::vector<std::vector<bool>> closed(Row, std::vector<bool>(Col, false));

    Node* start = new Node{startRow, startCol, 0, 0, 0, nullptr};
    start->h = abs(endRow - startRow) + abs(endCol - startCol);
    start->f = start->g + start->h;
    openList.push(start);

    Node* found = nullptr;

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->row == endRow && current->col == endCol) {
            found = current;
            break;
        }

        closed[current->row][current->col] = true;

        for (int i = 0; i < 4; i++) {
            int nr = current->row + dr[i];
            int nc = current->col + dc[i];

            if (nr < 0 || nr >= Row || nc < 0 || nc >= Col) continue;
            if (closed[nr][nc]) continue;
            if (obstacles[nr][nc]) continue;  // 장애물 무시

            Node* neighbor = new Node{nr, nc, current->g + 1, 0, 0, current};
            neighbor->h = (endRow - nr) + abs(endCol - nc);
            neighbor->f = neighbor->g + neighbor->h;

            openList.push(neighbor);


            QWidget* widget = gridLayout->itemAtPosition(nr, nc)->widget();
            if (widget) widget->setStyleSheet("background-color: lightgreen;");
        }
    }


    if (found) {
        Node* asd = found;
        while (asd->parent) {
            QWidget* widget = gridLayout->itemAtPosition(asd->row, asd->col)->widget();
            if (widget) widget->setStyleSheet("background-color: yellow;");
            asd = asd->parent;
        }
    }
}

void MyWidget::on_spinBox_3_valueChanged(int arg1)
{
    obstacle_percentage = Col * Row * arg1 * 0.01;
}

void MyWidget::on_pushButton_3_clicked(bool checked)
{
    if (Row <= 0 || Col <= 0) return;

    std::srand(std::time(nullptr));

    // 장애물 배열 초기화 → 클래스 멤버 사용
    obstacles.assign(Row, std::vector<bool>(Col, false));

    int obstacleCount = obstacle_percentage;
    qDebug() << "장애물 개수:" << obstacleCount;

    int placed = 0;
    while (placed < obstacleCount) {
        int r = std::rand() % Row;
        int c = std::rand() % Col;

        // 시작점과 끝점은 제외
        if ((r == startRow && c == startCol) || (r == endRow && c == endCol))
            continue;

        if (!obstacles[r][c]) {
            obstacles[r][c] = true;
            QWidget* w1 = gridLayout->itemAtPosition(r, c)->widget();
            QWidget* w2 = gridLayout2->itemAtPosition(r, c)->widget();
            if (w1) w1->setStyleSheet("background-color: black;");
            if (w2) w2->setStyleSheet("background-color: black;");
            placed++;
        }
    }
}

struct DNode {
    int row, col;
    int dist;
    DNode* parent;
};

struct CompareDNode {
    bool operator()(DNode* a, DNode* b) {
        return a->dist > b->dist;
    }
};

void MyWidget::Dijkstra_algorithm() {
    if (startRow1 == -1 || endRow1 == -1) {
        qDebug() << "다익스트라: 시작점과 끝점을 지정해주십쇼.";
        return;
    }

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    std::priority_queue<DNode*, std::vector<DNode*>, CompareDNode> openList;
    std::vector<std::vector<bool>> closed(Row, std::vector<bool>(Col, false));

    DNode* start = new DNode{startRow1, startCol1, 0, nullptr};
    openList.push(start);

    DNode* found = nullptr;

    while (!openList.empty()) {
        DNode* current = openList.top();
        openList.pop();

        if (current->row == endRow1 && current->col == endCol1) {
            found = current;
            break;
        }

        if (closed[current->row][current->col]) continue;
        closed[current->row][current->col] = true;

        for (int i = 0; i < 4; i++) {
            int nr = current->row + dr[i];
            int nc = current->col + dc[i];

            if (nr < 0 || nr >= Row || nc < 0 || nc >= Col) continue;
            if (closed[nr][nc]) continue;
            if (obstacles[nr][nc]) continue;  // 장애물은 무시

            DNode* neighbor = new DNode{nr, nc, current->dist + 1, current};
            openList.push(neighbor);

            // 탐색 중인 셀 표시
            QWidget* w = gridLayout2->itemAtPosition(nr, nc)->widget();
            if (w) w->setStyleSheet("background-color: lightgreen;");
        }
    }


    if (found) {
        DNode* cur = found;
        while (cur->parent) {
            QWidget* w = gridLayout2->itemAtPosition(cur->row, cur->col)->widget();
            if (w) w->setStyleSheet("background-color: yellow;");
            cur = cur->parent;
        }
    }
}

