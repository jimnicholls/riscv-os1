project('riscv-os1', 'c',
    version: configure_file(input: 'VERSION', output: 'VERSION', copy: true),
    license: 'MIT',
    license_files: 'LICENSE',
    meson_version: '>=1.5.0',
    default_options: [
        'default_library=static',
        'prefer_static=true',
        'c_std=gnu2x',
    ],
)

sources = []
subdir('src')

add_project_arguments(
    '-ffreestanding', '-nostartfiles', '-nostdlib', '-nodefaultlibs',
    '-march=rv64gc_zba_zbb_zbc_zbs_zcb_zfa_zicond_zicntr_zihpm_smaia_smstateen',
    '-mabi=lp64d', '-mcmodel=medany', '-misa-spec=2.2', '-Wa,--mpriv-spec=1.12',
    '-minline-strlen', '-minline-strcmp', '-minline-strncmp', '-mrelax', '-mriscv-attribute',
    language: 'c', native: false,
)

add_project_link_arguments(
    '-ffreestanding', '-nostartfiles', '-nostdlib', '-nodefaultlibs',
    '-march=rv64gc_zba_zbb_zbc_zbs_zcb_zfa_zicond_zicntr_zihpm_smaia_smstateen',
    '-mabi=lp64d', '-mcmodel=medany', '-misa-spec=2.2', '-Wa,--mpriv-spec=1.12',
    '-Wl,-T' + files('riscv64-virt-1mb.ld')[0].full_path(),
    '-Wl,-melf64lriscv,--gc-sections,--no-warn-rwx-segments',
    language: 'c', native: false,
)

executable('riscv-os1', sources,
    include_directories: include_directories('src'),
    native: false
)
