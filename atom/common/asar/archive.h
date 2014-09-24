// Copyright (c) 2014 GitHub, Inc. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_COMMON_ASAR_ARCHIVE_H_
#define ATOM_COMMON_ASAR_ARCHIVE_H_

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class DictionaryValue;
}

namespace asar {

class Archive : public base::RefCounted<Archive> {
 public:
  struct FileInfo {
    FileInfo() : size(0), offset(0) {}
    uint32 size;
    uint64 offset;
  };

  struct Stats : public FileInfo {
    Stats() : is_file(true), is_directory(false), is_link(false) {}
    bool is_file;
    bool is_directory;
    bool is_link;
  };

  explicit Archive(const base::FilePath& path);

  // Read and parse the header.
  bool Init();

  // Get the info of a file.
  bool GetFileInfo(const base::FilePath& path, FileInfo* info);

  // Fs.stat(path).
  bool Stat(const base::FilePath& path, Stats* stats);

  base::FilePath path() const { return path_; }
  base::DictionaryValue* header() const { return header_.get(); }

 private:
  friend class base::RefCounted<Archive>;
  virtual ~Archive();

  base::FilePath path_;
  uint32 header_size_;
  scoped_ptr<base::DictionaryValue> header_;

  DISALLOW_COPY_AND_ASSIGN(Archive);
};

}  // namespace asar

#endif  // ATOM_COMMON_ASAR_ARCHIVE_H_
