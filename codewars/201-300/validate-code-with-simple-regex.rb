def validate_code(code)
  /\A[123]/ === code.to_s
end
