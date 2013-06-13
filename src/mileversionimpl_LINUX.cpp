#include "mileversion/mileversion.h"
#include "mileversion/mileversionimpl_LINUX.h"
#include "mileversion/exceptions.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

namespace mileversion {

mileversionimpl::mileversionimpl(const std::string &filename) : 
	_filename(filename), _haveinfo(false)
{
	/* Check libelf version first */
	elf_version(EV_CURRENT);
	
	int fd;
	if ((fd=open(filename.c_str(), O_RDONLY))==-1)
		return;

	Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
	if (!elf)
	{
		close(fd);
		return;
	}
	
	size_t shstrndx;
	if (elf_getshdrstrndx (elf, &shstrndx ) != 0)
	{
		close(fd);
		elf_end(elf);
		return;
	}
	
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	Elf_Data *edata = NULL;
	GElf_Sym sym;
	int symbol_count;
	int i;
	
	// find .data section and "versionid" symbol
	while((scn = elf_nextscn(elf, scn)) != 0)
	{
		gelf_getshdr(scn, &shdr);
		char *name = elf_strptr(elf, shstrndx, shdr.sh_name);
		
		if(shdr.sh_type == SHT_SYMTAB)
		{
			// edata points to our symbol table
			edata = elf_getdata(scn, edata);
			
			// how many symbols are there? this number comes from the size of
			// the section divided by the entry size
			symbol_count = shdr.sh_size / shdr.sh_entsize;
			
			for(i = 0; i < symbol_count; i++)
			{
				gelf_getsym(edata, i, &sym);
				char *symbolname = elf_strptr(elf, shdr.sh_link, sym.st_name);
				char *versionstart;
				if ((versionstart = strstr(symbolname, MILEVERSION_VERSION_STR)) != NULL)
				{
					versionstart += strlen(MILEVERSION_VERSION_STR);
					
					int mh, ml, nh, nl;
					if (sscanf(versionstart, "%d_%d_%d_%d", &mh, &ml, &nh, &nl) == 4)
					{
						_haveinfo = true;
						
						char vinfo[50];
						sprintf(vinfo, "%d.%d.%d.%d", mh, ml, nh, nl);
						
						_fileversion = vinfo;
						break;
					}
				}
			}
		}
		
		if (_haveinfo)
			break;
	}
	
	close(fd);
	elf_end(elf);
}

mileversionimpl::~mileversionimpl()
{

}

bool mileversionimpl::haveInfo()
{
	return _haveinfo;
}

const std::string &mileversionimpl::fileVersion()
{
	return _fileversion;
}

};
