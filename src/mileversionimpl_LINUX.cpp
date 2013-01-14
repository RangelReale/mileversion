#include "mileversion/mileversionimpl_LINUX.h"
#include "mileversion/exceptions.h"

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>

namespace mileversion {

mileversionimpl::mileversionimpl(const std::string &filename, const std::string &versionid) : 
	_filename(filename), _haveinfo(false)
{
	/* Check libelf version first */
	elf_version(EV_CURRENT);
	
	int fd;
	if ((fd=open(filename.c_str(), O_RDONLY))==-1)
		return;

	Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
	size_t shstrndx;
	if (elf_getshdrstrndx (elf, &shstrndx ) != 0)
	{
		elf_end(elf);
		return;
	}
	
	Elf_Scn *scn = NULL, *datascn = NULL;
	GElf_Shdr shdr;
	Elf_Data *edata = NULL;
	GElf_Sym sym, versionsym;
	int symbol_count;
	int i;
	bool isversionsym = false;
	
	// find .data section and "versionid" symbol
	while((scn = elf_nextscn(elf, scn)) != 0)
	{
		gelf_getshdr(scn, &shdr);
		char *name = elf_strptr(elf, shstrndx, shdr.sh_name);
		printf("%s\n", name);
		
		if (strcmp(name, ".data") == 0)
			datascn = scn;
		
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
				if (strstr(symbolname, versionid.c_str()) != NULL)
				{
					printf("%s\n", symbolname);
					
					isversionsym = true;
					versionsym = sym;
				}
			}
		}
	}
	
	if (!datascn || !isversionsym)
	{
		elf_end(elf);
		return;
	}
	
	if (gelf_getshdr(datascn, &shdr) == NULL)
	{
		elf_end(elf);
		return;
	}

	/*
	int n = 0;
	Elf_Data *data = NULL;
	while ( n < shdr.sh_size && ( data = elf_getdata (datascn, data )) != NULL ) {
		char *p = ( char *) data->d_buf ;
		while ( p < ( char *) data->d_buf + data->d_size ) {
			//if ( vis ( pc , *p , VIS_WHITE , 0))
				//printf ( "%c" , p );
				putchar(*p);
			n++; p++;
			//( void ) putchar(( n % 16) ?'':'\n' );
			//if (!(n % 16)) putchar('\n');
		}
	}
	( void ) putchar ( '\n' );
	*;
	
	
	/*
	edata = NULL;
	if ((edata = elf_getdata(datascn, edata)) != NULL)
	{
		printf("%p\n", edata);
	}
	*/
	
	
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
