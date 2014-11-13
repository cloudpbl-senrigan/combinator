{
  'includes': [
    'common.gypi',
    '../combinator/combinator.gypi',
  ],
  'targets': [
    {
      'target_name': 'combinator',
      'product_name': 'SenriganCombinator',
      'type': 'executable',
      'include_dirs': [
        '../combinator',
      ],
      'sources':
      [
        '../combinator/main.cpp',
      ]
    }
  ]
}