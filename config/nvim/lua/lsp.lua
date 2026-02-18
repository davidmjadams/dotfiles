require("mason").setup()
require("mason-lspconfig").setup({ ensure_installed = { "ts_ls" } })

vim.lsp.config("ts_ls", {})
vim.lsp.enable("ts_ls")
