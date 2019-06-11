#include <climits>
#include <cstdio>
#include <cstdlib>
using namespace std;

long long Fingerprint(long long x) {
    const long long kMul = 0x9ddfea08eb382d69ULL;
    x *= kMul, x ^= x >> 47;
    x *= kMul, x ^= x >> 47;
    x *= kMul, x ^= x >> 47;
    return x * kMul;
}

long long Random() {
    static long long Seed = 2;
    return Fingerprint(Seed++) & LONG_LONG_MAX;
}

struct RBST {
    RBST *ChildL, *ChildR;
    int Size;
    long long Data;

    RBST() { ChildL = ChildR = 0; }
};

int GetSize(const RBST* root) { return root ? root->Size : 0; }

int FirstIndex(const RBST* root, long long x) {
    if (!root) return 0;
    if (x <= root->Data) return FirstIndex(root->ChildL, x);
    int sizeL = GetSize(root->ChildL);
    return FirstIndex(root->ChildR, x) + sizeL + 1;
}

long long Select(const RBST* root, int index) {
    int sizeL = GetSize(root->ChildL);
    if (index == sizeL) return root->Data;
    if (index < sizeL) return Select(root->ChildL, index);
    return Select(root->ChildR, index - sizeL - 1);
}

RBST* SetSize(RBST* root) {
    root->Size = GetSize(root->ChildL) + GetSize(root->ChildR) + 1;
    return root;
}

void Split(RBST* root, long long x, RBST** treeL, RBST** treeR) {
    if (!root) {
        *treeL = *treeR = 0;
    } else if (x <= root->Data) {
        Split(root->ChildL, x, treeL, &root->ChildL);
        *treeR = SetSize(root);
    } else {
        Split(root->ChildR, x, &root->ChildR, treeR);
        *treeL = SetSize(root);
    }
}

RBST* Join(RBST* treeL, RBST* treeR) {
    int sizeL = GetSize(treeL);
    int sizeR = GetSize(treeR);
    int size = sizeL + sizeR;
    if (size == 0) return 0;
    if (Random() % size < sizeL) {
        treeL->ChildR = Join(treeL->ChildR, treeR);
        return SetSize(treeL);
    } else {
        treeR->ChildL = Join(treeL, treeR->ChildL);
        return SetSize(treeR);
    }
}

RBST* InsertAsRoot(RBST* root, long long item) {
    RBST *newRoot = new RBST;
    newRoot->Data = item;
    Split(root, item + 1, &newRoot->ChildL, &newRoot->ChildR);
    return SetSize(newRoot);
}

RBST* Insert(RBST* root, long long item) {
    if (Random() % (GetSize(root) + 1) == 0) {
        return InsertAsRoot(root, item);
    } else if (item < root->Data) {
        root->ChildL = Insert(root->ChildL, item);
    } else {
        root->ChildR = Insert(root->ChildR, item);
    }
    return SetSize(root);
}

RBST* Remove(RBST* root, long long item) {
    RBST *tree1, *tree2, *tree3, *tree4 = 0;
    Split(root, item, &tree1, &tree2);
    Split(tree2, item + 1, &tree2, &tree3);
    if (tree2) tree4 = Join(tree2->ChildL, tree2->ChildR);
    delete tree2;
    return Join(Join(tree1, tree4), tree3);
}

void Clear(RBST* root) {
    if (root->ChildL) Clear(root->ChildL);
    if (root->ChildR) Clear(root->ChildR);
    delete root;
}

struct Solution {
    int N;
    RBST *Tree;

    void Solve() {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            int operation;
            scanf("%d", &operation);
            switch (operation) {
                case 1: {
                    long long x;
                    scanf("%lld", &x);
                    Tree = Insert(Tree, x);
                    break;
                }
                case 2: {
                    long long x;
                    scanf("%lld", &x);
                    Tree = Remove(Tree, x);
                    break;
                }
                case 3: {
                    long long x;
                    scanf("%lld", &x);
                    printf("%d\n", FirstIndex(Tree, x) + 1);
                    break;
                }
                case 4: {
                    int rank;
                    scanf("%d", &rank);
                    printf("%lld\n", Select(Tree, rank - 1));
                    break;
                }
                case 5: {
                    long long x;
                    scanf("%lld", &x);
                    printf("%lld\n", Select(Tree, FirstIndex(Tree, x) - 1));
                    break;
                }
                case 6: {
                    long long x;
                    scanf("%lld", &x);
                    printf("%lld\n", Select(Tree, FirstIndex(Tree, x + 1)));
                    break;
                }
            }
        }
        Clear(Tree);
    }
};

int main() {
    Solution().Solve();
    return 0;
}
