/* NAppGUI containers VS STL */

#include "coreall.h"
#include "nowarn.hxx"
#include <vector>
#include <set>
#include <algorithm>
#include "warn.hxx"

using namespace std;

struct Product
{
    uint32_t id;
    char_t code[64];
    char_t description[256];
    real32_t price;
};

/*---------------------------------------------------------------------------*/

static void i_init(Product *product, uint32_t id, real32_t price)
{
    cassert_no_null(product);
    product->id = id;
    bstd_sprintf(product->code, 64, "Code-[%d]", id);
    bstd_sprintf(product->description, 256, "Description-[%d]", id);
    product->price = price;
}

/*---------------------------------------------------------------------------*/

static Product *i_create(uint32_t id, real32_t price)
{
    Product *product = heap_new(Product);
    i_init(product, id, price);
    return product;
}

/*---------------------------------------------------------------------------*/

static int i_compare(const Product *p1, const Product *p2)
{
    return (int)p1->id - (int)p2->id;
}

/*---------------------------------------------------------------------------*/

struct i_stl_compare
{
    inline bool operator()(const Product &lhs, const Product &rhs) const  
    { return lhs.id < rhs.id; }

    inline bool operator()(const Product* lhs, const Product* rhs) const  
    { return lhs->id < rhs->id; }

};

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    bool_t err;
    uint32_t n;
    uint32_t *ids;
    Product *products;
    Product **pproducts;
    ArrSt(Product) *arrst;
    ArrPt(Product) *arrpt;
    SetSt(Product) *setst;
    SetPt(Product) *setpt;
    vector<Product> stl_arrst;
    vector<Product*> stl_arrpt;
    set<Product,i_stl_compare> stl_setst;
    set<Product*,i_stl_compare> stl_setpt;
    Clock *clock;
    real64_t t;

    core_start();

    if (argc == 2)
    {
        n = str_to_u32(argv[1], 10, &err);
        if (err == TRUE)
        {
            log_printf("Use: stlcmp [size].");
            return 0;
        }
    }
    else
    {
        n = 2000000;
    }

    bstd_printf("NAppGUI Containers vs STL.\n");
    
    // Create the elements. This time is out of the test
    // The elements will be shuffled randomly
    ids = heap_new_n(n, uint32_t);
    for (uint32_t i = 0; i < n; ++i)
        ids[i] = i;
    bmath_rand_seed(526);
    bmem_shuffle_n(ids, n, uint32_t);

    products = heap_new_n(n, Product);
    pproducts = heap_new_n(n, Product*);
    for (uint32_t i = 0; i < n; ++i)
    {
        i_init(&products[i], ids[i], 100.f + i);
        pproducts[i] = i_create(ids[i], 100.f + i);
    }

    arrst = arrst_create(Product);
    arrpt = arrpt_create(Product);
    setst = setst_create(i_compare, Product);
    setpt = setpt_create(i_compare, Product);
    
    clock = clock_create(0.);
    bstd_printf("- Created %d elements of %lu bytes\n", n, sizeof(Product));
    bstd_printf("- Starting...\n");

    // NAppGUI struct array
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
    {
        Product *p = arrst_append1(arrst, Product);
        *p = products[i];
    }
    arrst_sort(arrst, i_compare, Product);
    t = clock_elapsed(clock);
    bstd_printf("- Add to ArrSt(Product) and sort: %.6f\n", t);

    // STL struct array
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        stl_arrst.push_back(products[i]);
    sort(stl_arrst.begin(), stl_arrst.end(), i_stl_compare());
    t = clock_elapsed(clock);
    bstd_printf("- Add to vector<Product> and sort: %.6f\n", t);

    // NAppGUI pointer array
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        arrpt_append(arrpt, pproducts[i], Product);
    arrpt_sort(arrpt, i_compare, Product);
    t = clock_elapsed(clock);
    bstd_printf("- Add to ArrPt(Product) and sort: %.6f\n", t);

    // STL pointer array
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        stl_arrpt.push_back(pproducts[i]);
    sort(stl_arrpt.begin(), stl_arrpt.end(), i_stl_compare());
    t = clock_elapsed(clock);
    bstd_printf("- Add to vector<Product*> and sort: %.6f\n", t);

    // NAppGUI struct set
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
    {
        Product *product = setst_insert(setst, &products[i], Product);
        *product = products[i];
    }
    t = clock_elapsed(clock);
    bstd_printf("- Add to SetSt(Product): %.6f\n", t);

    // STL struct set
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        stl_setst.insert(products[i]);
    t = clock_elapsed(clock);
    bstd_printf("- Add to set<Product>: %.6f\n", t);

    // NAppGUI pointer set
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        setpt_insert(setpt, pproducts[i], Product);
    t = clock_elapsed(clock);
    bstd_printf("- Add to SetPt(Product): %.6f\n", t);

    // STL pointer set
    clock_reset(clock);
    for (uint32_t i = 0; i < n; ++i)
        stl_setpt.insert(pproducts[i]);
    t = clock_elapsed(clock);
    bstd_printf("- Add to set<Product*>: %.6f\n", t);

    // Verify the sorting correctness
    arrst_foreach(product, arrst, Product)
        if (product->id != product_i)
            bstd_printf("- Sorting error!!!!!\n");
    arrst_end();

    for (size_t i = 0; i < stl_arrst.size(); ++i)
    {
        if (i != stl_arrst[i].id)
            bstd_printf("- Sorting error!!!!!\n");
    }

    arrpt_foreach(product, arrpt, Product)
        if (product->id != product_i)
            bstd_printf("- Sorting error!!!!!\n");
    arrpt_end();

    for (size_t i = 0; i < stl_arrpt.size(); ++i)
    {
        if (i != stl_arrpt[i]->id)
            bstd_printf("- Sorting error!!!!!\n");
    }

    setst_foreach(product, setst, Product)
        if (product->id != product_i)
            bstd_printf("- Sorting error!!!!!\n");
    setst_fornext(product, setst, Product);

    uint32_t ic = 0;
    for (set<Product,i_stl_compare>::iterator i = stl_setst.begin(); i != stl_setst.end(); ++i)
    {
        if (i->id != ic++)
            bstd_printf("- Sorting error!!!!!\n");
    }

    setpt_foreach(product, setpt, Product)
        if (product->id != product_i)
            bstd_printf("- Sorting error!!!!!\n");
    setpt_fornext(product, setpt, Product);

    ic = 0;
    for (set<Product*,i_stl_compare>::iterator i = stl_setpt.begin(); i != stl_setpt.end(); ++i)
    {
        if ((*i)->id != ic++)
            bstd_printf("- Sorting error!!!!!\n");
    }

    clock_destroy(&clock);
    arrst_destroy(&arrst, NULL, Product);
    arrpt_destroy(&arrpt, NULL, Product);
    setst_destroy(&setst, NULL, Product);
    setpt_destroy(&setpt, NULL, Product);

    for (uint32_t i = 0; i < n; ++i)
        heap_delete(&pproducts[i], Product);

    heap_delete_n(&products, n, Product);
    heap_delete_n(&pproducts, n, Product*);
    heap_delete_n(&ids, n, uint32_t);

    core_finish();
    return 0;
}

