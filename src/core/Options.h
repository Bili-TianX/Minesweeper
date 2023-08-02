#pragma once

#include "../game/BlockType.h"

const int MINE_STYLE_COUNT = 7;

class Options {
 public:
  static auto getInstance() -> Options *;

  [[nodiscard]] auto isSoundEnabled() const -> bool;
  void setSoundEnabled(bool enabled);

  [[nodiscard]] auto getMineImage() const -> QPixmap;
  [[nodiscard]] auto getMineImage(int index) const -> QPixmap;
  [[nodiscard]] auto getMineStyle() const -> int;
  void setMineStyle(int index);

  [[nodiscard]] auto getMineCount() const -> int;
  void setMineCount(int count);

 private:
  Options();
  ~Options();

  QSettings settings{"settings.ini", QSettings::IniFormat};

  bool sound_enabled;
  int mine_style, mine_count;

  // 图像资源
  QMap<int, QPixmap> mine_images;
};

#define OPTIONS Options::getInstance()

#define PLAY_SOUND(x)                \
  do {                               \
    if (OPTIONS->isSoundEnabled()) { \
      (x).play();                    \
    }                                \
  } while (false)
