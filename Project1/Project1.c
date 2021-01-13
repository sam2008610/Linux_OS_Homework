#include <linux/init.h>//包含了模組的初始化的巨集定義及一些其他函式的初始化函式
#include <linux/module.h>//核心模組必備標頭檔案
#include <linux/mm.h>//// 記憶體管理相關標頭檔案，含有頁面大小定義和一些頁面釋放函式原型。
#include <linux/mm_types.h>//記憶體管理相關標頭檔案
#include <linux/sched.h>//程序排程相關標頭檔案
#include <linux/export.h>//必要的標頭檔案
#include <linux/highmem.h>
#include <linux/proc_fs.h>

//定義全域性變數

//static unsigned long cr0, cr3;//定義CR0和CR3

//列印頁機制中的一些重要引數

/*static void get_pgtable_macro(void)
{
	cr0 = read_cr0();//獲得CR0暫存器的值
	cr3 = read_cr3_pa();//獲得CR3暫存器的值
	printk("cr0 = 0x%lx, cr3 = 0x%lx\n", cr0, cr3);//列印CR0和CR3的值

	//_SHIFT巨集用來描述線性地址中相應欄位所能對映區域大小的位數

	printk("PGDIR_SHIFT = %d\n", PGDIR_SHIFT);//列印頁全域性目錄項能對映的區域大小的位數
	printk("P4D_SHIFT = %d\n", P4D_SHIFT);//列印P4D目錄項能對映的區域大小的位數
	printk("PUD_SHIFT = %d\n", PUD_SHIFT);//列印頁上級目錄項能對映的區域大小的位數
	printk("PMD_SHIFT = %d\n", PMD_SHIFT);//列印頁中間目錄項可以對映的區域大小的位數
	printk("PAGE_SHIFT = %d\n", PAGE_SHIFT);//列印page_offset欄位所能對映區域大小的位數

	//指示相應頁目錄表中項的個數

	printk("PTRS_PER_PGD = %d\n", PTRS_PER_PGD);//列印頁全域性目錄項數
	printk("PTRS_PER_P4D = %d\n", PTRS_PER_P4D);//列印P4D目錄項數
	printk("PTRS_PER_PUD = %d\n", PTRS_PER_PUD);//列印頁上級目錄項數
	printk("PTRS_PER_PMD = %d\n", PTRS_PER_PMD);//列印頁中級目錄項數
	printk("PTRS_PER_PTE = %d\n", PTRS_PER_PTE);//列印頁表項數
	printk("PAGE_MASK = 0x%lx\n", PAGE_MASK);//頁內偏移掩碼，遮蔽page_offset欄位
}
*/
//線性地址轉換為實體地址

static unsigned long vaddr2paddr(struct task_struct* task)
{
	//建立變數儲存頁目錄

	unsigned long paddr = 0;
	unsigned long page_addr = 0;
	unsigned long long page_offset = 0;

	//獲取頁全域性目錄PGD，第一個引數當前程序的mm_struct，所有程序共享一個核心頁表

	pgd_t* pgd = pgd_offset(task->mm, task->mm->mmap_base);//獲得pgd的地址

	//printk("pgd_val = 0x%lx, pgd_index = %lu\n", pgd_val(*pgd), pgd_index(task->mm->mmap_base));//列印pgd地址和索引
	if (pgd_none(*pgd))//判斷pgd頁表項是否為空
	{
		printk("not mapped in pgd\n");
		return -1;
	}

	//獲取頁上級目錄PUD

	pud_t* pud = pud_offset(pud, task->mm->mmap_base);//獲得pud的地址
	//printk("pud_val = 0x%lx, pud_index = %lu\n", pud_val(*pud), pud_index(task->mm->mmap_base));//列印pud地址和索引

	if (pud_none(*pud)) //判斷pud頁表項是否為空
	{
		printk("not mapped in pud\n");
		return -1;
	}

	//獲取頁中間目錄PMD

	pmd_t* pmd = pmd_offset(pud, task->mm->mmap_base); //獲得pmd的地址
	//printk("pmd_val = 0x%lx, pmd_index = %lu\n", pmd_val(*pmd), pmd_index(task->mm->mmap_base));//列印pmd地址和索引

	if (pmd_none(*pmd)) ////判斷pmd頁表項是否為空
	{
		printk("not mapped in pmd\n");
		return -1;
	}

	pte_t* pte = pte_offset_kernel(pmd, task->mm->mmap_base);//獲得pte的地址
	//printk("pte_val = 0x%lx, ptd_index = %lu\n", pte_val(*pte), pte_index(task->mm->mmap_base));//列印pte地址和索引

	if (pte_none(*pte)) //判斷pte頁表項是否為空
	{
		printk("not mapped in pte\n");
		return -1;
	}

	page_addr = pte_val(*pte) & PAGE_MASK; //獲得頁框的實體地址
	page_offset = task->mm->mmap_base & ~PAGE_MASK; //獲得頁偏移地址
	paddr = page_addr | page_offset; //獲得實體地址

	//printk("page_addr = %lx, page_offset = %lx\n", page_addr, page_offset);
	//printk("task->mm->mmap_base = %lx, paddr = %lx\n", task->mm->mmap_base, paddr);//列印虛擬地址和轉換後的實體地址

	return paddr;
}

static unsigned long 
//載入核心模組

static int __init v2p_init(void)
{
	struct task_struct* task_list;
	for_each_process(task_list)
	{
		printk("This is process!\n");
		//printk("%s [%lx]\n", task_list->comm, vaddr2paddr(task_list));
		if(task_list->mm==NULL){
			printk("Nothing in here .Bitch!\n");
			continue;
		}
		printk("[%p]\n",task_list->mm->pgd);
		unsigned long addr = 0;
		pud_t* pud;
		pud = pud_offset(task_list->mm->pgd, addr);	
		printk(", *pud=%016llx", pud_val(*pud));
		
		
		pud_t* pud = pud_offset(pud, task_list->mm->pgd);//獲得pud的地址
		//printk("pud_val = 0x%lx, pud_index = %lu\n", pud_val(*pud), pud_index(task->mm->mmap_base));//列印pud地址和索引

		if (pud_none(*pud)) //判斷pud頁表項是否為空
		{
			printk("not mapped in pud\n");
			return -1;
		}
		printk("The pgdoffset is %p.\n",pud);
		// unsigned long addr = 0;
		// pgd_t* pgd;
		// pgd = pgd_offset(task_list->mm, addr);
		// printk("[%08lx] *pgd=%016llx", addr, pgd_val(*pgd));
		// printk("Process End!\n");
	}
	return 0;
}

//解除安裝核心模組

static void __exit v2p_exit(void)
{
	printk(KERN_INFO "Cleaning up.\n");
}

//入口、出口、許可證

MODULE_LICENSE("GPL"); //許可證
module_init(v2p_init);//核心入口函式
module_exit(v2p_exit);//核心出口函式


void show_pgd(struct mm_struct* mm, unsigned long addr)
{

}
/*--------------------------------------------------------------*/
// 印值
/*

void show_pte(struct mm_struct* mm, unsigned long addr)
{
	pgd_t* pgd;

	if (!mm)
		mm = &init_mm;
	//print pointer by using p
	pr_alert("pgd = %p\n", mm->pgd);
	pgd = pgd_offset(mm, addr);
	pr_alert("[%08lx] *pgd=%016llx", addr, pgd_val(*pgd));

	do {
		pud_t* pud;
		pmd_t* pmd;
		pte_t* pte;

		if (pgd_none(*pgd) || pgd_bad(*pgd))
			break;

		pud = pud_offset(pgd, addr);

		//打印64 bit的数据可以用%016llx
		printk(", *pud=%016llx", pud_val(*pud));
		if (pud_none(*pud) || pud_bad(*pud))
			break;

		pmd = pmd_offset(pud, addr);
		printk(", *pmd=%016llx", pmd_val(*pmd));
		if (pmd_none(*pmd) || pmd_bad(*pmd))
			break;

		pte = pte_offset_map(pmd, addr);
		printk(", *pte=%016llx", pte_val(*pte));
		pte_unmap(pte);
	} while (0);

	printk("\n");
}
*/

// print kernel page table
/*
for (; pgd_idx < PTRS_PER_PGD; pgd_idx++) {
	unsigned long pgd_cur = pgd_idx * PGDIR_SIZE;
	pmd = pmd_offset((pud_t*)(pgd_base + pgd_idx), pgd_cur);

	for (pmd_idx = 0; pmd_idx < 448	//PTRS_PER_PMD
		; pmd_idx++) {
		unsigned long pmd_cur = pgd_cur + pmd_idx * PMD_SIZE;

		if (pmd_present(pmd[pmd_idx])) {
			pte = pte_offset_kernel((pmd_t*)(pmd + pmd_idx), pmd_cur);

			pte1 = pmd_val(*((pmd_t*)(pmd + pmd_idx)));

			if ((((unsigned long)pte1) >> 7) & 0x1)

			{
				//打印2M页
			}

			else

			{
				for (pte_ofs = 0; pte_ofs < PTRS_PER_PTE; pte_ofs++) {
					unsigned long pg_cur = pmd_cur + pte_ofs * PAGE_SIZE;

					if (pte_present(pte[pte_ofs]))

					{
						//打印4kb页
					}
				}
			}
		}
	}
}
*/
/*
static void __init kernel_physical_mapping_init(pgd_t * pgd_base)
{
	unsigned long pfn;
	pgd_t* pgd;
	pmd_t* pmd;
	pte_t* pte;
	int pgd_idx, pmd_idx, pte_ofs;

	//因为内核的线性地址空间是从0xC0000000开始的，所以这里我们只需要初始化内核全局页目录从0x300开始的项

	pgd_idx = pgd_index(PAGE_OFFSET);      //3
	pgd = pgd_base + pgd_idx;              //pgd指向当前的目录
	pfn = 0;                               //需要被映射的物理页框号，从物理地址0开始
	//初始化从3开始的每个页全局目录项，PTRS_PER_PGD为总项数512

	for (; pgd_idx < PTRS_PER_PGD; pgd++, pgd_idx++)
	{
		pmd = one_md_table_init(pgd);
		if (pfn >= max_low_pfn)                     //max_low_pfn代表被内核直接映射的最后一个物理页框的页框号
			continue;

		//初始化每个页中间目录项，前面说到启用了物理地址扩展的32位x86系统中，使用三级映射，
		//而没有启用物理地址扩展的32位系统，其实只使用了其中的两级，虽然在软件结构中PMD依然存在，
		//但实际只是一个摆设。内核通过将PTRS_PER_PMD设为1，并且在one_md_table_init初始化PMD的函数中
		//直接将PMD的第一项初始化为指向其地址的PGD项本身，完成了一个"原地"的映射。也就是说，
		//此时的每一个页目录项，既表示一个页中间目录描述符，也表示一个页表 

		for (pmd_idx = 0; pmd_idx < PTRS_PER_PMD && pfn < max_low_pfn; pmd++, pmd_idx++)
		{
			unsigned int address = pfn * PAGE_SIZE + PAGE_OFFSET;

			//Map with big pages if possible, otherwise create normal page tables.

			if (cpu_has_pse) {
				unsigned int address2 = (pfn + PTRS_PER_PTE - 1) * PAGE_SIZE + PAGE_OFFSET + PAGE_SIZE - 1;
				if (is_kernel_text(address) || is_kernel_text(address2))
					set_pmd(pmd, pfn_pmd(pfn, PAGE_KERNEL_LARGE_EXEC));
				else
					set_pmd(pmd, pfn_pmd(pfn, PAGE_KERNEL_LARGE));
				pfn += PTRS_PER_PTE;
			}
			else {
				pte = one_page_table_init(pmd);
				//最后初始化每个页表项，也就是每个物理页框的描述符。注意pfn++表示页框号依次加1，
				//而其初始值为0，也就是把物理地址从0开始的页框，直接映射到内核线性地址0xC0000000开始的空间内
				//，映射的方式与临时内核页表相似，只不过范围更大了
				for (pte_ofs = 0; pte_ofs < PTRS_PER_PTE && pfn < max_low_pfn; pte++, pfn++, pte_ofs++, address += PAGE_SIZE)
				{
					if (is_kernel_text(address))
						set_pte(pte, pfn_pte(pfn, PAGE_KERNEL_EXEC));
					else
						set_pte(pte, pfn_pte(pfn, PAGE_KERNEL));
				}
			}
		}
	}
}
*/