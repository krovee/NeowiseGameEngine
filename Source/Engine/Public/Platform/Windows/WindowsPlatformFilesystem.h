#pragma once

#include "WindowsBase.h"
#include <Base/UUID.h>
#include <Base/StringView.h>

namespace Neowise::Platform::Windows {
    class CFS;

    /** 
    * 
    */
    class NW_API CFileDescriptor {
    public:
        ~CFileDescriptor();
        CFileDescriptor(CFS& fs, const CUUID& uuid, TInt64& refCount, TUint size, TBool autoRelease);

        CFileDescriptor(const CFileDescriptor&);
        CFileDescriptor(CFileDescriptor&&);

        CFileDescriptor& operator=(const CFileDescriptor&) = default;
        CFileDescriptor& operator=(CFileDescriptor&&) = default;

        TUint getSize() const;

        TUint getData(TUint offset, TUint size) const;
        TUint getData(TUint size) const;
        TUint getData() const;

    private:
        CFS*	_fs;
        CUUID	_uuid = {};
        TUint	_size = {};
        TInt64*	_refCount;
        TBool	_autoRelease = kTrue;
    };

    /** 
    * 
    */
    class NW_API CFS {
    public:
        CFS();
        ~CFS();

        CFileDescriptor create(const CStringView& filepath);
        CFileDescriptor open(const CStringView& filepath);
        CFileDescriptor createOrOpen(const CStringView& filepath);
        void			release(CFileDescriptor& fd);

        void*			read(const CFileDescriptor& fd);
        void*			read(const CFileDescriptor& fd, TUint size);
        void*			read(const CFileDescriptor& fd, TUint offset, TUint size);

        void			write(CFileDescriptor& fd, const void* data, TUint size);
        void			write(CFileDescriptor& fd, const void* data, TUint offset, TUint size);

    private:
        friend class CFileDescriptor;
    private:
        // Hash table holds entries which are contains reference count 
        // of file HANDLE. If int64 value is <= 0, release HANDLE.
        // TODO(krovee): CHashtable<CUUID, CPair<int64, HANDLE> >	_FDs = {};
    };
}
