#ifndef LIB_ecall_H
#define LIB_ecall_H

#include "../call_status_value.h"


// =====================================================================================================================


#define ecall_ecall_i0(func_num)      \
    asm (                               \
        "li a7, %1\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        : "=r" (csv)                    \
        : "n" (func_num)                \
        : "a7"                          \
    )

#define ecall_ecall_i1(func_num, i1_constraint, i1_name, i1_inst) \
    asm (                               \
        #i1_inst " a0, %2\n\t"          \
        "li a7, %1\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        : "=r" (csv)                    \
        : "n" (func_num),               \
          #i1_constraint (i1_name)      \
        : "a7", "a0"                    \
    )

#define ecall_ecall_i2(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst) \
    asm (                               \
        #i1_inst " a0, %2\n\t"          \
        #i2_inst " a1, %3\n\t"          \
        "li a7, %1\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        : "=r" (csv)                    \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name)      \
        : "a7", "a0", "a1"              \
    )

#define ecall_ecall_i3(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst) \
    asm (                               \
        #i1_inst " a0, %2\n\t"          \
        #i2_inst " a1, %3\n\t"          \
        #i3_inst " a2, %4\n\t"          \
        "li a7, %1\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        : "=r" (csv)                    \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name)      \
        : "a7", "a0", "a1", "a2"        \
    )

#define ecall_ecall_i4(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst, i4_constraint, i4_name, i4_inst) \
    asm (                               \
        #i1_inst " a0, %2\n\t"          \
        #i2_inst " a1, %3\n\t"          \
        #i3_inst " a2, %4\n\t"          \
        #i4_inst " a3, %5\n\t"          \
        "li a7, %1\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        : "=r" (csv)                    \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name),     \
          #i4_constraint (i4_name)      \
        : "a7", "a0", "a1", "a2", "a3"  \
    )

#define ecall_ecall_i0o1(func_num, o1_name) \
    asm (                               \
        "li a7, %2\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name)                \
        : "n" (func_num)                \
        : "a7", "a0"                    \
    )

#define ecall_ecall_i1o1(func_num, i1_constraint, i1_name, i1_inst, o1_name) \
    asm (                               \
        #i1_inst " a0, %3\n\t"          \
        "li a7, %2\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name)      \
        : "a7", "a0"                    \
    )

#define ecall_ecall_i2o1(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, o1_name) \
    asm (                               \
        #i1_inst " a0, %3\n\t"          \
        #i2_inst " a1, %4\n\t"          \
        "li a7, %2\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name)      \
        : "a7", "a0", "a1"              \
    )

#define ecall_ecall_i3o1(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst, o1_name) \
    asm (                               \
        #i1_inst " a0, %3\n\t"          \
        #i2_inst " a1, %4\n\t"          \
        #i3_inst " a2, %5\n\t"          \
        "li a7, %2\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name)      \
        : "a7", "a0", "a1", "a2"        \
    )

#define ecall_ecall_i4o1(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst, i4_constraint, i4_name, i4_inst, o1_name) \
    asm (                               \
        #i1_inst " a0, %3\n\t"          \
        #i2_inst " a1, %4\n\t"          \
        #i3_inst " a2, %5\n\t"          \
        #i4_inst " a2, %6\n\t"          \
        "li a7, %2\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name),     \
          #i4_constraint (i4_name)      \
        : "a7", "a0", "a1", "a2"        \
    )

#define ecall_ecall_i0o2(func_num, o1_name, o2_name) \
    asm (                               \
        "li a7, %3\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        "mv %2, a1\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name),               \
          "=r" (o2_name)                \
        : "n" (func_num)                \
        : "a7", "a0", "a1"              \
    )

#define ecall_ecall_i1o2(func_num, i1_constraint, i1_name, i1_inst, o1_name, o2_name) \
    asm (                               \
        #i1_inst " a0, %4\n\t"          \
        "li a7, %3\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        "mv %2, a1\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name),               \
          "=r" (o2_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name)      \
        : "a7", "a0", "a1"              \
    )

#define ecall_ecall_i2o2(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, o1_name, o2_name) \
    asm (                               \
        #i1_inst " a0, %4\n\t"          \
        #i2_inst " a1, %5\n\t"          \
        "li a7, %3\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        "mv %2, a1\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name),               \
          "=r" (o2_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name)      \
        : "a7", "a0", "a1"              \
    )

#define ecall_ecall_i3o2(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst, o1_name, o2_name) \
    asm (                               \
        #i1_inst " a0, %4\n\t"          \
        #i2_inst " a1, %5\n\t"          \
        #i3_inst " a2, %6\n\t"          \
        "li a7, %3\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        "mv %2, a1\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name),               \
          "=r" (o2_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name)      \
        : "a7", "a0", "a1", "a2"        \
    )

#define ecall_ecall_i4o2(func_num, i1_constraint, i1_name, i1_inst, i2_constraint, i2_name, i2_inst, i3_constraint, i3_name, i3_inst, i4_constraint, i4_name, i4_inst, o1_name, o2_name) \
    asm (                               \
        #i1_inst " a0, %4\n\t"          \
        #i2_inst " a1, %5\n\t"          \
        #i3_inst " a2, %6\n\t"          \
        #i4_inst " a3, %7\n\t"          \
        "li a7, %3\n\t"                 \
        "ecall\n\t"                     \
        "mv %0, a7\n\t"                 \
        "mv %1, a0\r\n"                 \
        "mv %2, a1\r\n"                 \
        : "=r" (csv),                   \
          "=r" (o1_name),               \
          "=r" (o2_name)                \
        : "n" (func_num),               \
          #i1_constraint (i1_name),     \
          #i2_constraint (i2_name),     \
          #i3_constraint (i3_name),     \
          #i4_constraint (i4_name)      \
        : "a7", "a0", "a1", "a2"        \
    )


// =====================================================================================================================


#define ecall_decl_a0(func_name)                  \
    CallStatusValue func_name()

#define ecall_defn_a0(func_name, func_num)        \
    ecall_decl_a0(func_name) {                    \
        CallStatusValue csv;                        \
        ecall_ecall_i0(func_num);                 \
        return csv;                                 \
    }

#define ecall_decl_a1(func_name, a1_type, a1_name)            \
    CallStatusValue func_name(a1_type a1_name)

#define ecall_defn_a1(func_name, func_num, a1_type, a1_name)  \
    ecall_decl_a1(func_name, a1_type, a1_name) {              \
        CallStatusValue csv;                                    \
        ecall_ecall_i1(func_num, r, a1_name, mv);             \
        return csv;                                             \
    }

#define ecall_decl_a2(func_name, a1_type, a1_name, a2_type, a2_name)              \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name)

#define ecall_defn_a2(func_name, func_num, a1_type, a1_name, a2_type, a2_name)    \
    ecall_decl_a2(func_name, a1_type, a1_name, a2_type, a2_name) {                \
        CallStatusValue csv;                                                        \
        ecall_ecall_i2(func_num, r, a1_name, mv, r, a2_name, mv);                 \
        return csv;                                                                 \
    }

#define ecall_decl_a3(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name)            \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name, a3_type a3_name)

#define ecall_defn_a3(func_name, func_num, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name)  \
    ecall_decl_a3(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name) {              \
        CallStatusValue csv;                                                                        \
        ecall_ecall_i3(func_num, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv);                 \
        return csv;                                                                                 \
    }


// =====================================================================================================================


#define ecall_decl_r1(func_name, r1_type, r1_name)              \
    CallStatusValue func_name(r1_type* r1_name)

#define ecall_defn_r1(func_name, func_num, r1_type, r1_name)    \
    ecall_decl_r1(func_name, r1_type, r1_name) {                \
        CallStatusValue csv;                                        \
        r1_type r1;                                                 \
        ecall_ecall_i0o1(func_num, r1);                           \
        if (csv >= CSV_OK) {                                        \
            *r1_name = r1;                                          \
        }                                                           \
        return csv;                                                 \
    }

#define ecall_decl_a1r1(func_name, a1_type, a1_name, r1_type, r1_name)            \
    CallStatusValue func_name(a1_type a1_name, r1_type* r1_name)

#define ecall_defn_a1r1(func_name, func_num, a1_type, a1_name, r1_type, r1_name)  \
    ecall_decl_a1r1(func_name, a1_type, a1_name, r1_type, r1_name) {              \
        CallStatusValue csv;                                                        \
        r1_type r1;                                                                 \
        ecall_ecall_i1o1(func_num, r, a1_name, mv, r1);                           \
        if (csv >= CSV_OK) {                                                        \
            *r1_name = r1;                                                          \
        }                                                                           \
        return csv;                                                                 \
    }

#define ecall_decl_a2r1(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name)              \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name, r1_type* r1_name)

#define ecall_defn_a2r1(func_name, func_num, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name)    \
    ecall_decl_a2r1(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name) {                \
        CallStatusValue csv;                                                                            \
        r1_type r1;                                                                                     \
        ecall_ecall_i2o1(func_num, r, a1_name, mv, r, a2_name, mv, r1);                               \
        if (csv >= CSV_OK) {                                                                            \
            *r1_name = r1;                                                                              \
        }                                                                                               \
        return csv;                                                                                     \
    }

#define ecall_decl_a3r1(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name)            \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name, a3_type a3_name, r1_type* r1_name)

#define ecall_defn_a3r1(func_name, func_num, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name)  \
    ecall_decl_a3r1(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name) {              \
        CallStatusValue csv;                                                                                            \
        r1_type r1;                                                                                                     \
        ecall_ecall_i3o1(func_num, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv, r1);                               \
        if (csv >= CSV_OK) {                                                                                            \
            *r1_name = r1;                                                                                              \
        }                                                                                                               \
        return csv;                                                                                                     \
    }


// =====================================================================================================================


#define ecall_decl_r2(func_name, r1_type, r1_name, r2_type, r2_name)            \
    CallStatusValue func_name(r1_type* r1_name, r2_type* r2_name)

#define ecall_defn_r2(func_name, func_num, r1_type, r1_name, r2_type, r2_name)  \
    ecall_decl_r2(func_name, r1_type, r1_name, r2_type, r2_name) {              \
        CallStatusValue csv;                                                        \
        r1_type r1;                                                                 \
        r2_type r2;                                                                 \
        ecall_ecall_i0o2(func_num, r1, r2);                                       \
        if (csv >= CSV_OK) {                                                        \
            *r1_name = r1;                                                          \
            *r2_name = r2;                                                          \
        }                                                                           \
        return csv;                                                                 \
    }

#define ecall_decl_a1r2(func_name, a1_type, a1_name, r1_type, r1_name, r2_type, r2_name)              \
    CallStatusValue func_name(a1_type a1_name, r1_type* r1_name, r2_type* r2_name)

#define ecall_defn_a1r2(func_name, func_num, a1_type, a1_name, r1_type, r1_name, r2_type, r2_name)    \
    ecall_decl_a1r2(func_name, a1_type, a1_name, r1_type, r1_name, r2_type, r2_name) {                \
        CallStatusValue csv;                                                                            \
        r1_type r1;                                                                                     \
        r2_type r2;                                                                                     \
        ecall_ecall_i1o2(func_num, r, a1_name, mv, r1, r2);                                           \
        if (csv >= CSV_OK) {                                                                            \
            *r1_name = r1;                                                                              \
            *r2_name = r2;                                                                              \
        }                                                                                               \
        return csv;                                                                                     \
    }

#define ecall_decl_a2r2(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name, r2_type, r2_name)            \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name, r1_type* r1_name, r2_type* r2_name)

#define ecall_defn_a2r2(func_name, func_num, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name, r2_type, r2_name)  \
    ecall_decl_a2r2(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name, r2_type, r2_name) {              \
        CallStatusValue csv;                                                                                            \
        r1_type r1;                                                                                                     \
        r2_type r2;                                                                                                     \
        ecall_ecall_i2o2(func_num, r, a1_name, mv, r, a2_name, mv, r1, r2);                                           \
        if (csv >= CSV_OK) {                                                                                            \
            *r1_name = r1;                                                                                              \
            *r2_name = r2;                                                                                              \
        }                                                                                                               \
        return csv;                                                                                                     \
    }

#define ecall_decl_a3r2(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name, r2_type, r2_name)              \
    CallStatusValue func_name(a1_type a1_name, a2_type a2_name, a3_type a3_name, r1_type* r1_name, r2_type* r2_name)

#define ecall_defn_a3r2(func_name, func_num, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name, r2_type, r2_name)    \
    ecall_decl_a3r2(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name, r2_type, r2_name) {                \
        CallStatusValue csv;                                                                                                                \
        r1_type r1;                                                                                                                         \
        r2_type r2;                                                                                                                         \
        ecall_ecall_i3o2(func_num, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv, r1, r2);                                               \
        if (csv >= CSV_OK) {                                                                                                                \
            *r1_name = r1;                                                                                                                  \
            *r2_name = r2;                                                                                                                  \
        }                                                                                                                                   \
        return csv;                                                                                                                         \
    }


// =====================================================================================================================


#define ecall_defn_v(func_name, func_num, v)    \
    ecall_decl_a0(func_name) {                    \
        CallStatusValue csv;                        \
        ecall_ecall_i1(func_num, n, v, li);       \
        return csv;                                 \
    }

#define ecall_defn_va1(func_name, func_num, v, a1_type, a1_name)  \
    ecall_decl_a1(func_name, a1_type, a1_name) {                  \
        CallStatusValue csv;                                        \
        ecall_ecall_i2(func_num, n, v, li, r, a1_name, mv);       \
        return csv;                                                 \
    }

#define ecall_defn_va2(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name)    \
    ecall_decl_a2(func_name, a1_type, a1_name, a2_type, a2_name) {                    \
        CallStatusValue csv;                                                            \
        ecall_ecall_i3(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv);           \
        return csv;                                                                     \
    }

#define ecall_defn_va3(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name)  \
    ecall_decl_a3(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name) {                  \
        CallStatusValue csv;                                                                            \
        ecall_ecall_i4(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv);           \
        return csv;                                                                                     \
    }


// =====================================================================================================================


#define ecall_defn_vr1(func_name, func_num, v, r1_type, r1_name)    \
    ecall_decl_r1(func_name, r1_type, r1_name) {                    \
        CallStatusValue csv;                                            \
        r1_type r1;                                                     \
        ecall_ecall_i1o1(func_num, n, v, li, r1);                     \
        if (csv >= CSV_OK) {                                            \
            *r1_name = r1;                                              \
        }                                                               \
        return csv;                                                     \
    }

#define ecall_defn_va1r1(func_name, func_num, v, a1_type, a1_name, r1_type, r1_name)  \
    ecall_decl_a1r1(func_name, a1_type, a1_name, r1_type, r1_name) {                  \
        CallStatusValue csv;                                                            \
        r1_type r1;                                                                     \
        ecall_ecall_i2o1(func_num, n, v, li, r, a1_name, mv, r1);                     \
        if (csv >= CSV_OK) {                                                            \
            *r1_name = r1;                                                              \
        }                                                                               \
        return csv;                                                                     \
    }

#define ecall_defn_va2r1(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name)    \
    ecall_decl_a2r1(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name) {                    \
        CallStatusValue csv;                                                                                \
        r1_type r1;                                                                                         \
        ecall_ecall_i3o1(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv, r1);                         \
        if (csv >= CSV_OK) {                                                                                \
            *r1_name = r1;                                                                                  \
        }                                                                                                   \
        return csv;                                                                                         \
    }

#define ecall_defn_va3r1(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name)  \
    ecall_decl_a3r1(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name) {                  \
        CallStatusValue csv;                                                                                                \
        r1_type r1;                                                                                                         \
        ecall_ecall_i4o1(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv, r1);                         \
        if (csv >= CSV_OK) {                                                                                                \
            *r1_name = r1;                                                                                                  \
        }                                                                                                                   \
        return csv;                                                                                                         \
    }


// =====================================================================================================================


#define ecall_defn_vr2(func_name, func_num, v, r1_type, r1_name, r2_type, r2_name)  \
    ecall_decl_r2(func_name, r1_type, r1_name, r2_type, r2_name) {                  \
        CallStatusValue csv;                                                            \
        r1_type r1;                                                                     \
        r2_type r2;                                                                     \
        ecall_ecall_i1o2(func_num, n, v, li, r1, r2);                                 \
        if (csv >= CSV_OK) {                                                            \
            *r1_name = r1;                                                              \
            *r2_name = r2;                                                              \
        }                                                                               \
        return csv;                                                                     \
    }

#define ecall_defn_va1r2(func_name, func_num, v, a1_type, a1_name, r1_type, r1_name, r2_type, r2_name)    \
    ecall_decl_a1r2(func_name, a1_type, a1_name, r1_type, r1_name, r2_type, r2_name) {                    \
        CallStatusValue csv;                                                                                \
        r1_type r1;                                                                                         \
        r2_type r2;                                                                                         \
        ecall_ecall_i2o2(func_num, n, v, li, r, a1_name, mv, r1, r2);                                     \
        if (csv >= CSV_OK) {                                                                                \
            *r1_name = r1;                                                                                  \
            *r2_name = r2;                                                                                  \
        }                                                                                                   \
        return csv;                                                                                         \
    }

#define ecall_defn_va2r2(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name, r2_type, r2_name)  \
    ecall_decl_a2r2(func_name, a1_type, a1_name, a2_type, a2_name, r1_type, r1_name, r2_type, r2_name) {                  \
        CallStatusValue csv;                                                                                                \
        r1_type r1;                                                                                                         \
        r2_type r2;                                                                                                         \
        ecall_ecall_i3o2(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv, r1, r2);                                     \
        if (csv >= CSV_OK) {                                                                                                \
            *r1_name = r1;                                                                                                  \
            *r2_name = r2;                                                                                                  \
        }                                                                                                                   \
        return csv;                                                                                                         \
    }

#define ecall_defn_va3r2(func_name, func_num, v, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name, r2_type, r2_name)    \
    ecall_decl_a3r2(func_name, a1_type, a1_name, a2_type, a2_name, a3_type, a3_name, r1_type, r1_name, r2_type, r2_name) {                    \
        CallStatusValue csv;                                                                                                                    \
        r1_type r1;                                                                                                                             \
        r2_type r2;                                                                                                                             \
        ecall_ecall_i4o2(func_num, n, v, li, r, a1_name, mv, r, a2_name, mv, r, a3_name, mv, r1, r2);                                         \
        if (csv >= CSV_OK) {                                                                                                                    \
            *r1_name = r1;                                                                                                                      \
            *r2_name = r2;                                                                                                                      \
        }                                                                                                                                       \
        return csv;                                                                                                                             \
    }


#endif //LIB_ecall_H
