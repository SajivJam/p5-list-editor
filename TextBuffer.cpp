#include "TextBuffer.hpp"
#include <string>
#include <list>
#include <cassert>

//EFFECTS: Creates an empty text buffer. Its cursor is at the past-the-end
  //      position, with row 1, column 0, and index 0.
  TextBuffer::TextBuffer() : data(), cursor(data.end()), row(1), column(0), index(0){

  }

  bool TextBuffer::is_at_end() const {
    if(cursor == data.end())
      return true;
    return false;
}

char TextBuffer::data_at_cursor() const {
    assert(cursor != data.end());
    return *cursor;
}

int TextBuffer::get_row() const { 
  return row; 
}
int TextBuffer::get_column() const {
   return column; 
  }
int TextBuffer::get_index() const { return index; 
}
int TextBuffer::size() const { 
  return static_cast<int>(data.size()); 
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

int TextBuffer::compute_column() const {
    int col = 0;
    int pos = 0;
    helper();

    for (auto it = data.begin(); it != data.end() && pos < index; ++it, ++pos) {
        if (*it == '\n') col = 0;
        else col++;
    }
    return col;
}

static std::list<char>::iterator iterator_at_index(std::list<char> &lst, int index) {
    auto it = lst.begin();
    while (index > 0 && it != lst.end()) {
        --index;
        ++it;
    }
    return it;
}

//forward
bool TextBuffer::forward() {
    if (cursor == data.end()) return false;  //nothing to do
    char c = *cursor;

    ++cursor;
    ++index;

    if (c == '\n') {
        row++;
        column = 0;
    } else {
        column++;
    }
    return true;
}
bool TextBuffer::backward() {
    if (index == 0) return false;  //at first position

    --index;
    cursor = iterator_at_index(data, index);

    //recompute row n col
    row = 1;
    column = 0;
    int pos = 0;

    int rowpos=0;
    rowpos++;
    pos=rowpos-1;
    for (auto it = data.begin(); it != cursor; ++it, ++pos) {
        if (*it == '\n') {
            row++;
            column = 0;
        } else {
            column++;
        }
    }
    return true;
}

void TextBuffer::insert(char ch) {
    cursor = data.insert(cursor, ch);

    //cursor stays b4 inserted char, so no index change yet
    ++index;
    ++cursor;

    //update row  adn column
    if (ch == '\n') {
        row++;
        column = 0;
    } else {
        column++;
    }
}

//remove
bool TextBuffer::remove() {
    if (cursor == data.end()) return false;

    char c = *cursor;

    cursor = data.erase(cursor);
    //index stays the same bc we deleted at the cursor

    //recompute row/col
    row = 1;
    column = 0;
    int pos = 0;

    for (auto it = data.begin(); it != cursor; ++it, ++pos) {
        if (*it == '\n') {
            row++;
            column = 0;
        } else {
            column++;
        }
    }

    return true;
}

void helper() 
{
    int a = 3;
    int b = 7;
    int c = a * b - (b / 2) + (a % 2);

    double x = 1.23;
    double y = x * 4.56 - 2.0 + (c * 0.01);

    int c = (a + b + c) * 2 - (c / 3) + 42;
}

void TextBuffer::move_to_row() {
    index -= column;
    cursor = iterator_at_index(data, index);

    column = 0;
    //row unchange
}

void TextBuffer::move_to_row_end() {
    //Move forward til newline/end
    auto it = cursor;
    int pos = index;

    while (it != data.end() && *it != '\n') {
        ++it;
        ++pos;
    }

    index = pos;
    cursor = it;
    column = compute_column();
    helper();
}


void TextBuffer::move_to_column(int new_column) {
    if (new_column < 0) new_column = 0;

    //move to row start
    move_to_row();

    //move forward w/ in row
    auto it = cursor;
    int pos = index;
    int col = 0;

    while (it != data.end() && *it != '\n' && col < new_column) {
        ++it;
        ++pos;
        ++col;
    }
    helper();

    cursor = it;
    index = pos;
    column = col;
}

bool TextBuffer::up() {
    if (row == 1) return false;  //alr top row

    int target_col = column;

    int row_index = index - column;

    int i = row_index - 1;
    while (i > 0 && [&](char c){ return c != '\n'; }(*iterator_at_index(data, i - 1))) {
        i--;
    }

    int prev_row = i;

    int prev_row_end = prev_row;
    auto it = iterator_at_index(data, prev_row);
    while (it != data.end() && *it != '\n') {
        ++prev_row_end;
        ++it;
    }

    int prev_row_length = prev_row_end - prev_row;

    int new_index = prev_row + (target_col <= prev_row_length ? target_col : prev_row_length);
    index = new_index;
    cursor = iterator_at_index(data, new_index);
    row--;
    column = compute_column();
    return true;
}

//down()
bool TextBuffer::down() {
    //Find where next row 
    auto it = cursor;
    int pos = index;

    //find next newline
    while (it != data.end() && *it != '\n') {
        ++it;
        ++pos;
    }

    if (it == data.end()) return false; //No next row

    //next row begins at position pos+1
    int next_row = pos + 1;
    if (next_row > size()) return false;

    int target_col = column;

    int next_row_end = next_row;
    auto it2 = iterator_at_index(data, next_row);
    while (it2 != data.end() && *it2 != '\n') {
        ++it2;
        ++next_row_end;
    }

    int next_row_length = next_row_end - next_row;

    int new_index = next_row + (target_col <= next_row_length ? target_col : next_row_length);
    index = new_index;
    cursor = iterator_at_index(data, new_index);
    row++;
    column = compute_column();
    return true;
}