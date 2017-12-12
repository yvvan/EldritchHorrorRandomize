#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QScroller>

static void ClearLayout(QBoxLayout* layout) {
  auto* item = layout->takeAt(0);
  while (item) {
    QBoxLayout* childLayout = static_cast<QBoxLayout*>(item->layout());
    if (childLayout) {
      ClearLayout(childLayout);
      delete childLayout;
      item = layout->takeAt(0);
      continue;
    }
    delete item->widget();
    delete item;
    item = layout->takeAt(0);
  }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);
  ui_->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui_->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  QScroller::grabGesture(ui_->scrollArea, QScroller::LeftMouseButtonGesture);

  ShowExpansions();
  //ShowMainWindow();
}

MainWindow::~MainWindow() = default;

void MainWindow::ShowExpansions() {
  ui_->mainLayout->addWidget(std::make_unique<QLabel>("Select expansions").release());
  for (auto i = 0; i < kExpansionsNumber; ++i) {
    auto checkbox = std::make_unique<QCheckBox>(kExpansions[i]);
    checkbox->setChecked(true);
    ui_->mainLayout->addWidget(checkbox.release());
  }
  auto next_button = std::make_unique<QPushButton>("Next");
  ui_->mainLayout->addWidget(next_button.release());
  ui_->mainLayout->addStretch();
}

void MainWindow::ShowMainWindow() {
  auto expansions_button = std::make_unique<QPushButton>("Back to expansions selection");
  ui_->mainLayout->addWidget(expansions_button.release());

  auto setup_button = std::make_unique<QPushButton>("Random Set Up");
  ui_->mainLayout->addWidget(setup_button.release());

  auto locations_button = std::make_unique<QPushButton>("Random Locations");
  ui_->mainLayout->addWidget(locations_button.release());

  auto characters_button = std::make_unique<QPushButton>("Random Characters");
  ui_->mainLayout->addWidget(characters_button.release());

  ui_->mainLayout->addStretch();
}
