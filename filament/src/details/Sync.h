/*
 * Copyright (C) 2025 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_DETAILS_SYNC_H
#define TNT_FILAMENT_DETAILS_SYNC_H

#include "downcast.h"

#include <filament/Sync.h>

#include <condition_variable>
#include <mutex>

namespace filament {

class FEngine;

class FSync : public Sync {
public:
    FSync(FEngine& engine) noexcept;

    void terminate(FEngine& engine) noexcept;

    inline backend::SyncHandle getHandle() const noexcept {
        return mHwSync;
    }

private:
    backend::SyncHandle mHwSync;
    std::mutex mMutex;
    std::condition_variable mCV;

    // Invoked by the command queue once the underlying backend
    // handle has been set, which indicates that we can update wait calls
    // to use the underlying wait function.
    void processHandle() noexcept;
};

}

#endif // TNT_FILAMENT_DETAILS_SYNC_H
