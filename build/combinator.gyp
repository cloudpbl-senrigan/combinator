{
  'includes': [
    'common.gypi',
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