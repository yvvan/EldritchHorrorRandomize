#pragma once

#include <QMainWindow>

#include <array>
#include <memory>

namespace Ui {
  class MainWindow;
}

static constexpr size_t kExpansionsNumber = 8;

static constexpr const std::array<const char*, kExpansionsNumber>
kExpansions = {"Forsaken Lore", "Mountains of Madness", "Strange Remnants", "Under the Pyramids ",
               "Signs of Carcosa", "The Dreamlands ", "Cities in Ruin ", "Masks of Nyarlathotep"};

class MainWindow : public QMainWindow {
  Q_OBJECT
  enum class ActiveScreen {
    Expansions = 0,
    Main = 1,
    Locations,
    Setup,
    Characters,
    None
  };
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void ChangeCurrent(ActiveScreen new_current);
  void ShowExpansions();
  void ShowMainWindow();
  void ShowCharacters();
  void ShowLocations();
  std::unique_ptr<Ui::MainWindow> ui_;
  std::array<bool, kExpansionsNumber> selected_expansions_;
  ActiveScreen current_screen_ = ActiveScreen::None;
};
