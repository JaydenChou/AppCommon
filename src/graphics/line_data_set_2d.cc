// This is free and unencumbered software released into the public domain.
// For more information, please refer to <http://unlicense.org/>

#include "appcommon/graphics/line_data_set_2d.h"

#include <algorithm>

LineDataSet2d::LineDataSet2d() {
  is_updated_ = false;
}

LineDataSet2d::~LineDataSet2d() {
  Clear();
}

void LineDataSet2d::Add(const Line2d* line) {
  data_.push_back(line);

  is_updated_ = false;
}

void LineDataSet2d::Clear() {
  for (auto iter = data_.begin(); iter != data_.end(); iter++) {
    const Line2d* line = *iter;
    delete line;
  }

  data_.clear();

  is_updated_ = false;
}

double LineDataSet2d::MaxX() const {
  if (is_updated_ == false) {
    Update();
  }

  return x_max_;
}

double LineDataSet2d::MaxY() const {
  if (is_updated_ == false) {
    Update();
  }

  return y_max_;
}

double LineDataSet2d::MinX() const {
  if (is_updated_ == false) {
    Update();
  }

  return x_min_;
}

double LineDataSet2d::MinY() const {
  if (is_updated_ == false) {
    Update();
  }

  return y_min_;
}

const std::list<const Line2d*>* LineDataSet2d::data() const {
  return &data_;
}

void LineDataSet2d::Update() const {
  // initializes
  x_min_ = 999999;
  x_max_ = -999999;

  y_min_ = 999999;
  y_max_ = -999999;

  // checks if data exists, exits if not
  if (data_.empty() == true) {
    return;
  }

  for (auto iter = data_.cbegin(); iter != data_.cend(); iter++) {
    const Line2d* line = *iter;

    x_min_ = std::min(line->p0.x, x_min_);
    x_min_ = std::min(line->p1.x, x_min_);
    x_max_ = std::max(line->p0.x, x_max_);
    x_max_ = std::max(line->p1.x, x_max_);

    y_min_ = std::min(line->p0.y, y_min_);
    y_min_ = std::min(line->p1.y, y_min_);
    y_max_ = std::max(line->p0.y, y_max_);
    y_max_ = std::max(line->p1.y, y_max_);
  }

  is_updated_ = true;
}
