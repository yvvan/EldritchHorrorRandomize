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
  selected_expansions_.fill(true);

  ShowExpansions();
}

MainWindow::~MainWindow() = default;

void MainWindow::ShowExpansions() {
  ui_->mainLayout->addWidget(std::make_unique<QLabel>("Select expansions").release());
  for (size_t i = 0; i < kExpansionsNumber; ++i) {
    auto checkbox = std::make_unique<QCheckBox>(kExpansions[i]);
    checkbox->setChecked(selected_expansions_[i]);
    ui_->mainLayout->addWidget(checkbox.release());
  }
  auto next_button = std::make_unique<QPushButton>("Next");
  QObject::connect(next_button.get(), &QPushButton::clicked, this, [this]() {
    auto check_box_list = ui_->scrollArea->findChildren<QCheckBox*>();
    for (size_t i = 0; i < kExpansionsNumber; ++i) {
      selected_expansions_[i] = check_box_list.at(static_cast<int>(i))->isChecked();
    }
    ChangeCurrent(ActiveScreen::Main);
  });
  ui_->mainLayout->addWidget(next_button.release());
  ui_->mainLayout->addStretch();
}

void MainWindow::ShowMainWindow() {
  auto expansions_button = std::make_unique<QPushButton>("Back to expansions selection");
  QObject::connect(expansions_button.get(), &QPushButton::clicked, this, [this]() {
    ChangeCurrent(ActiveScreen::Expansions);
  });
  ui_->mainLayout->addWidget(expansions_button.release());

  auto setup_button = std::make_unique<QPushButton>("Random set up");
  ui_->mainLayout->addWidget(setup_button.release());

  auto locations_button = std::make_unique<QPushButton>("Random locations");
  QObject::connect(locations_button.get(), &QPushButton::clicked, this, [this]() {
    ChangeCurrent(ActiveScreen::Locations);
  });
  ui_->mainLayout->addWidget(locations_button.release());

  auto characters_button = std::make_unique<QPushButton>("Random characters");
  ui_->mainLayout->addWidget(characters_button.release());

  ui_->mainLayout->addStretch();
}

void MainWindow::ShowLocations() {
  auto main_window_button = std::make_unique<QPushButton>("Back to main");
  QObject::connect(main_window_button.get(), &QPushButton::clicked, this, [this]() {
    ChangeCurrent(ActiveScreen::Main);
  });
  ui_->mainLayout->addWidget(main_window_button.release());

  auto random_location = std::make_unique<QPushButton>("Random location (any)");
  ui_->mainLayout->addWidget(random_location.release());

  auto random_city = std::make_unique<QPushButton>("Random city");
  ui_->mainLayout->addWidget(random_city.release());

  auto random_wilderness = std::make_unique<QPushButton>("Random wilderness");
  ui_->mainLayout->addWidget(random_wilderness.release());

  auto random_sea = std::make_unique<QPushButton>("Random sea");
  ui_->mainLayout->addWidget(random_sea.release());

  ui_->mainLayout->addStretch();
}

void MainWindow::ShowCharacters() {

}

void MainWindow::ChangeCurrent(ActiveScreen new_current) {
  ClearLayout(ui_->mainLayout);
  switch (new_current) {
  case ActiveScreen::Expansions:
    ShowExpansions();
    break;
  case ActiveScreen::Main:
    ShowMainWindow();
    break;
  case ActiveScreen::Locations:
    ShowLocations();
    break;
  case ActiveScreen::Characters:
    ShowCharacters();
    break;
  default:
    break;
  }
}
