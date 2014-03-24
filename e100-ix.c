#include <linux/hardirq.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/mii.h>
#include <linux/if_vlan.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <linux/string.h>
#include <linux/firmware.h>
#include <linux/rtnetlink.h>
#include <asm/unaligned.h>

#define DRIVER_NAME "e100-ix"

/* mem struct */ 

struct mem{
    struct {
        u32 signature;
        u32 result;
    } selftest;
    struct stats stats;
    u8 dump_buff[596];
};

/* declare only what we need to use */

struct nic {

    struct mem *mem;
    struct pci_dev *pdev;
    dma_addr_t dma_addr;
};

static const struct pci_device_id pci_datatable[] = {

    /* Initializing pci_device_id 
     * with entries from the Manual  
     */

    { PCI_DEVICE (0x8086, 0x1229)},

};

//TODO
static int driver_add (struct pci_dev *pdev, const struct pci_device_id *ent){

    struct net_device *netdev;
    struct nic *nic;
    int err;

    netdev = alloc_etherdev(sizeof(struct nic));
    if (!(netdev))
        return _ENOMEN;

};

/* Unregisters pci_driver struct */

static void remove (struct pci_dev *pdev){

    struct net_device *netdev = pci_get_drvdata(pdev);

    if (netdev){
        struct nic *nic = netdev_priv (netdev);
        unregister_netdev (netdev);
        if (nic->mem){
            pci_free_consistent(nic->pdev,sizeof(struct mem),
                    nic->mem,nic->dma_addr);
            nic->mem = NULL;
        }
        pci_iounmap(pdev, nic->csr);
        pci_pool_destro(nic->cbs_pool);
        free_netdev(netdev);
        pci_release_regions(pdev);
        pci_disable_device(pdev);
    }

};

static struct pci_driver e100-ix{
    /* Initialize the name of the driver */
    
    .name       = DRIVER_NAME,
    
    /* Initialize pci_device_id */
    
    .id_table   = pci_datatable,
    
    /* Called by PCI subsystem if 
     * devices from pci_datables exist 
    */

    .probe      = driver_add,
    
    .remove     = remove,

};
