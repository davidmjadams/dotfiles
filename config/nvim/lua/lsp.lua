require("mason").setup()
require("mason-lspconfig").setup({ensure_installed={"tsserver"}})
require("lspconfig").tsserver.setup({})
