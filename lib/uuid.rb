require_relative '../ext/uuid'

class UUID
  FORMATS = {
    :compact => '%08x%04x%04x%04x%012x',
    :default => '%08x-%04x-%04x-%04x-%012x',
    :urn     => 'urn:uuid:%08x-%04x-%04x-%04x-%012x',
  }
  include Comparable
  def to_s format=:default
    raise ArgumentError, "Invalid Format" unless FORMATS[format]
    FORMATS[format] % @uuid.unpack("H8H4H4H4H12").map {|v| v.to_i(16) }
  end
  def compact
    to_s :compact
  end
  def urn
    to_s :urn
  end
end
