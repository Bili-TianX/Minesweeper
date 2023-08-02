#include "Options.h"

#include "../game/Difficulty.h"

const auto DEFAULT_SOUND_ENABLED = true;
const auto DEFAULT_MINE_COUNT = Difficulty::DEFAULT.mineCount;
const auto DEFAULT_MINE_STYLE = 0;

Options::Options() {
  for (int i = 0; i < MINE_STYLE_COUNT; ++i) {
    mine_images[i] = {QStringLiteral(":/images/blocks/mines/%0.svg").arg(i)};
  }

  bool ok;

  sound_enabled =
      settings.value("sound_enabled", QVariant(DEFAULT_SOUND_ENABLED)).toBool();
  mine_style =
      settings.value("mine_style", QVariant(DEFAULT_MINE_STYLE)).toInt(&ok);
  if (!(ok && 0 <= mine_style && mine_style < MINE_STYLE_COUNT)) {
    mine_style = DEFAULT_MINE_STYLE;
  }
  mine_count =
      settings.value("mine_count", QVariant(DEFAULT_MINE_COUNT)).toInt(&ok);
  if (!(ok && 1 <= mine_count &&
        mine_count < Difficulty::DEFAULT.blockCount())) {
    mine_count = DEFAULT_MINE_COUNT;
  }
}

Options::~Options() {
  settings.setValue("sound_enabled", sound_enabled);
  settings.setValue("mine_style", mine_style);
  settings.setValue("mine_count", mine_count);
}
auto Options::getInstance() -> Options* {
  static Options instance;

  return &instance;
}

auto Options::isSoundEnabled() const -> bool { return sound_enabled; }
void Options::setSoundEnabled(bool enabled) { sound_enabled = enabled; }

auto Options::getMineImage() const -> QPixmap {
  return getMineImage(mine_style);
}

auto Options::getMineImage(int index) const -> QPixmap {
  return mine_images[index];
}

auto Options::getMineStyle() const -> int { return mine_style; }

void Options::setMineStyle(int index) { this->mine_style = index; }

auto Options::getMineCount() const -> int { return mine_count; }

void Options::setMineCount(int count) { this->mine_count = count; }